#include "qtscriptshell_QTextCodecPlugin.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qtextcodec.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QList<QByteArray>)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QTextCodecPlugin::QtScriptShell_QTextCodecPlugin(QObject*  parent)
    : QTextCodecPlugin(parent) {}

QtScriptShell_QTextCodecPlugin::~QtScriptShell_QTextCodecPlugin() {}

QList<QByteArray >  QtScriptShell_QTextCodecPlugin::aliases() const
{
    QScriptValue _q_function = __qtscript_self.property("aliases");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("aliases") & QScriptValue::QObjectMember)) {
        qFatal("QTextCodecPlugin::aliases() is abstract!");
    } else {
        return qscriptvalue_cast<QList<QByteArray > >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QTextCodecPlugin::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QTextCodecPlugin::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QTextCodec*  QtScriptShell_QTextCodecPlugin::createForMib(int  mib)
{
    QScriptValue _q_function = __qtscript_self.property("createForMib");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createForMib") & QScriptValue::QObjectMember)) {
        qFatal("QTextCodecPlugin::createForMib() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QTextCodec* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, mib)));
    }
}

QTextCodec*  QtScriptShell_QTextCodecPlugin::createForName(const QByteArray&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createForName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createForName") & QScriptValue::QObjectMember)) {
        qFatal("QTextCodecPlugin::createForName() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QTextCodec* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

void QtScriptShell_QTextCodecPlugin::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QTextCodecPlugin::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QTextCodecPlugin::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QTextCodecPlugin::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QTextCodecPlugin::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QTextCodecPlugin::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

QList<int >  QtScriptShell_QTextCodecPlugin::mibEnums() const
{
    QScriptValue _q_function = __qtscript_self.property("mibEnums");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mibEnums") & QScriptValue::QObjectMember)) {
        qFatal("QTextCodecPlugin::mibEnums() is abstract!");
    } else {
        return qscriptvalue_cast<QList<int > >(_q_function.call(__qtscript_self));
    }
}

QList<QByteArray >  QtScriptShell_QTextCodecPlugin::names() const
{
    QScriptValue _q_function = __qtscript_self.property("names");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("names") & QScriptValue::QObjectMember)) {
        qFatal("QTextCodecPlugin::names() is abstract!");
    } else {
        return qscriptvalue_cast<QList<QByteArray > >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QTextCodecPlugin::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QTextCodecPlugin::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

