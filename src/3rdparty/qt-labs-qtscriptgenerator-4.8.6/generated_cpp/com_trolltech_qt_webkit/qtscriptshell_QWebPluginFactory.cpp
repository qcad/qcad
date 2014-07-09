#include "qtscriptshell_QWebPluginFactory.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qurl.h>
#include <qwebpluginfactory.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QWebPluginFactory::Extension)
Q_DECLARE_METATYPE(QWebPluginFactory::ExtensionOption*)
Q_DECLARE_METATYPE(QWebPluginFactory::ExtensionReturn*)
Q_DECLARE_METATYPE(QWebPluginFactory::Plugin)
Q_DECLARE_METATYPE(QList<QWebPluginFactory::Plugin>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QWebPluginFactory::QtScriptShell_QWebPluginFactory(QObject*  parent)
    : QWebPluginFactory(parent) {}

QtScriptShell_QWebPluginFactory::~QtScriptShell_QWebPluginFactory() {}

void QtScriptShell_QWebPluginFactory::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QWebPluginFactory::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QObject*  QtScriptShell_QWebPluginFactory::create(const QString&  mimeType, const QUrl&  arg__2, const QStringList&  argumentNames, const QStringList&  argumentValues) const
{
    QScriptValue _q_function = __qtscript_self.property("create");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("create") & QScriptValue::QObjectMember)) {
        qFatal("QWebPluginFactory::create() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, mimeType)
            << qScriptValueFromValue(_q_engine, arg__2)
            << qScriptValueFromValue(_q_engine, argumentNames)
            << qScriptValueFromValue(_q_engine, argumentValues)));
    }
}

void QtScriptShell_QWebPluginFactory::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QWebPluginFactory::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QWebPluginFactory::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QWebPluginFactory::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QWebPluginFactory::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QWebPluginFactory::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

bool  QtScriptShell_QWebPluginFactory::extension(QWebPluginFactory::Extension  extension, const QWebPluginFactory::ExtensionOption*  option, QWebPluginFactory::ExtensionReturn*  output)
{
    QScriptValue _q_function = __qtscript_self.property("extension");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("extension") & QScriptValue::QObjectMember)) {
        return QWebPluginFactory::extension(extension, option, output);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, extension)
            << qScriptValueFromValue(_q_engine, const_cast<QWebPluginFactory::ExtensionOption *>(option))
            << qScriptValueFromValue(_q_engine, output)));
    }
}

QList<QWebPluginFactory::Plugin >  QtScriptShell_QWebPluginFactory::plugins() const
{
    QScriptValue _q_function = __qtscript_self.property("plugins");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("plugins") & QScriptValue::QObjectMember)) {
        qFatal("QWebPluginFactory::plugins() is abstract!");
    } else {
        return qscriptvalue_cast<QList<QWebPluginFactory::Plugin > >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QWebPluginFactory::refreshPlugins()
{
    QScriptValue _q_function = __qtscript_self.property("refreshPlugins");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("refreshPlugins") & QScriptValue::QObjectMember)) {
        QWebPluginFactory::refreshPlugins();
    } else {
        _q_function.call(__qtscript_self);
    }
}

bool  QtScriptShell_QWebPluginFactory::supportsExtension(QWebPluginFactory::Extension  extension) const
{
    QScriptValue _q_function = __qtscript_self.property("supportsExtension");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportsExtension") & QScriptValue::QObjectMember)) {
        return QWebPluginFactory::supportsExtension(extension);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, extension)));
    }
}

void QtScriptShell_QWebPluginFactory::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QWebPluginFactory::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

