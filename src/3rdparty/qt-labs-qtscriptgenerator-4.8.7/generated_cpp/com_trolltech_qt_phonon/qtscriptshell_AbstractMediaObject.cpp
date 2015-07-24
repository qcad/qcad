#include "qtscriptshell_AbstractMediaObject.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <mediasource.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Phonon::MediaSource)

QtScriptShell_AbstractMediaObject::QtScriptShell_AbstractMediaObject()
    : Phonon::MediaObjectInterface() {}

QtScriptShell_AbstractMediaObject::~QtScriptShell_AbstractMediaObject() {}

qint64  QtScriptShell_AbstractMediaObject::currentTime() const
{
    QScriptValue _q_function = __qtscript_self.property("currentTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentTime") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::currentTime() is abstract!");
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

QString  QtScriptShell_AbstractMediaObject::errorString() const
{
    QScriptValue _q_function = __qtscript_self.property("errorString");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorString") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::errorString() is abstract!");
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

Phonon::ErrorType  QtScriptShell_AbstractMediaObject::errorType() const
{
    QScriptValue _q_function = __qtscript_self.property("errorType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("errorType") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::errorType() is abstract!");
    } else {
        return qscriptvalue_cast<Phonon::ErrorType >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_AbstractMediaObject::hasVideo() const
{
    QScriptValue _q_function = __qtscript_self.property("hasVideo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasVideo") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::hasVideo() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_AbstractMediaObject::isSeekable() const
{
    QScriptValue _q_function = __qtscript_self.property("isSeekable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isSeekable") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::isSeekable() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_AbstractMediaObject::pause()
{
    QScriptValue _q_function = __qtscript_self.property("pause");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pause") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::pause() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_AbstractMediaObject::play()
{
    QScriptValue _q_function = __qtscript_self.property("play");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("play") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::play() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

int  QtScriptShell_AbstractMediaObject::prefinishMark() const
{
    QScriptValue _q_function = __qtscript_self.property("prefinishMark");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("prefinishMark") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::prefinishMark() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_AbstractMediaObject::remainingTime() const
{
    QScriptValue _q_function = __qtscript_self.property("remainingTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("remainingTime") & QScriptValue::QObjectMember)) {
        return Phonon::MediaObjectInterface::remainingTime();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_AbstractMediaObject::seek(qint64  milliseconds)
{
    QScriptValue _q_function = __qtscript_self.property("seek");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("seek") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::seek() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, milliseconds));
    }
}

void QtScriptShell_AbstractMediaObject::setNextSource(const Phonon::MediaSource&  source)
{
    QScriptValue _q_function = __qtscript_self.property("setNextSource");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setNextSource") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::setNextSource() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, source));
    }
}

void QtScriptShell_AbstractMediaObject::setPrefinishMark(int  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setPrefinishMark");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setPrefinishMark") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::setPrefinishMark() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractMediaObject::setSource(const Phonon::MediaSource&  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setSource");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSource") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::setSource() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractMediaObject::setTickInterval(int  interval)
{
    QScriptValue _q_function = __qtscript_self.property("setTickInterval");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setTickInterval") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::setTickInterval() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, interval));
    }
}

void QtScriptShell_AbstractMediaObject::setTransitionTime(int  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setTransitionTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setTransitionTime") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::setTransitionTime() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

Phonon::MediaSource  QtScriptShell_AbstractMediaObject::source() const
{
    QScriptValue _q_function = __qtscript_self.property("source");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("source") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::source() is abstract!");
    } else {
        return qscriptvalue_cast<Phonon::MediaSource >(_q_function.call(__qtscript_self));
    }
}

Phonon::State  QtScriptShell_AbstractMediaObject::state() const
{
    QScriptValue _q_function = __qtscript_self.property("state");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("state") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::state() is abstract!");
    } else {
        return qscriptvalue_cast<Phonon::State >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_AbstractMediaObject::stop()
{
    QScriptValue _q_function = __qtscript_self.property("stop");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("stop") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::stop() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

int  QtScriptShell_AbstractMediaObject::tickInterval() const
{
    QScriptValue _q_function = __qtscript_self.property("tickInterval");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("tickInterval") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::tickInterval() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_AbstractMediaObject::totalTime() const
{
    QScriptValue _q_function = __qtscript_self.property("totalTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("totalTime") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::totalTime() is abstract!");
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_AbstractMediaObject::transitionTime() const
{
    QScriptValue _q_function = __qtscript_self.property("transitionTime");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("transitionTime") & QScriptValue::QObjectMember)) {
        qFatal("AbstractMediaObject::transitionTime() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

