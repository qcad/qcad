#include "qtscriptshell_QWebPage.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <QEvent>
#include <QNetworkRequest>
#include <qwebframe.h>
#include <qwebpage.h>
#include <qwebpluginfactory.h>
#include <qwebsettings.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QWebFrame*)
//Q_DECLARE_METATYPE(QNetworkRequest)
Q_DECLARE_METATYPE(QWebPage::NavigationType)
Q_DECLARE_METATYPE(QWebPage::WebWindowType)
Q_DECLARE_METATYPE(QWebPage*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QWebPage::Extension)
Q_DECLARE_METATYPE(const QWebPage::ExtensionOption*)
Q_DECLARE_METATYPE(QWebPage::ExtensionReturn*)
Q_DECLARE_METATYPE(QString*)
Q_DECLARE_METATYPE(QWebPage::WebAction)

QtScriptShell_QWebPage::QtScriptShell_QWebPage(QObject*  parent)
    : QWebPage(parent) {}

QtScriptShell_QWebPage::~QtScriptShell_QWebPage() {}

bool  QtScriptShell_QWebPage::acceptNavigationRequest(QWebFrame*  frame, const QNetworkRequest&  request, QWebPage::NavigationType  type)
{
    QScriptValue _q_function = __qtscript_self.property("acceptNavigationRequest");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("acceptNavigationRequest") & QScriptValue::QObjectMember)) {
        return QWebPage::acceptNavigationRequest(frame, request, type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, frame)
            << qScriptValueFromValue(_q_engine, request)
            << qScriptValueFromValue(_q_engine, type)));
    }
}

QString  QtScriptShell_QWebPage::chooseFile(QWebFrame*  originatingFrame, const QString&  oldFile)
{
    QScriptValue _q_function = __qtscript_self.property("chooseFile");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("chooseFile") & QScriptValue::QObjectMember)) {
        return QWebPage::chooseFile(originatingFrame, oldFile);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, originatingFrame)
            << qScriptValueFromValue(_q_engine, oldFile)));
    }
}

QObject*  QtScriptShell_QWebPage::createPlugin(const QString&  classid, const QUrl&  url, const QStringList&  paramNames, const QStringList&  paramValues)
{
    QScriptValue _q_function = __qtscript_self.property("createPlugin");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createPlugin") & QScriptValue::QObjectMember)) {
        return QWebPage::createPlugin(classid, url, paramNames, paramValues);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, classid)
            << qScriptValueFromValue(_q_engine, url)
            << qScriptValueFromValue(_q_engine, paramNames)
            << qScriptValueFromValue(_q_engine, paramValues)));
    }
}

QWebPage*  QtScriptShell_QWebPage::createWindow(QWebPage::WebWindowType  type)
{
    QScriptValue _q_function = __qtscript_self.property("createWindow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createWindow") & QScriptValue::QObjectMember)) {
        return QWebPage::createWindow(type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QWebPage* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)));
    }
}

bool  QtScriptShell_QWebPage::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QWebPage::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QWebPage::extension(QWebPage::Extension  extension, const QWebPage::ExtensionOption*  option, QWebPage::ExtensionReturn*  output)
{
    QScriptValue _q_function = __qtscript_self.property("extension");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("extension") & QScriptValue::QObjectMember)) {
        return QWebPage::extension(extension, option, output);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, extension)
            << qScriptValueFromValue(_q_engine, const_cast<const QWebPage::ExtensionOption *>(option))
            << qScriptValueFromValue(_q_engine, output)));
    }
}

void QtScriptShell_QWebPage::javaScriptAlert(QWebFrame*  originatingFrame, const QString&  msg)
{
    QScriptValue _q_function = __qtscript_self.property("javaScriptAlert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("javaScriptAlert") & QScriptValue::QObjectMember)) {
        QWebPage::javaScriptAlert(originatingFrame, msg);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, originatingFrame)
            << qScriptValueFromValue(_q_engine, msg));
    }
}

bool  QtScriptShell_QWebPage::javaScriptConfirm(QWebFrame*  originatingFrame, const QString&  msg)
{
    QScriptValue _q_function = __qtscript_self.property("javaScriptConfirm");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("javaScriptConfirm") & QScriptValue::QObjectMember)) {
        return QWebPage::javaScriptConfirm(originatingFrame, msg);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, originatingFrame)
            << qScriptValueFromValue(_q_engine, msg)));
    }
}

void QtScriptShell_QWebPage::javaScriptConsoleMessage(const QString&  message, int  lineNumber, const QString&  sourceID)
{
    QScriptValue _q_function = __qtscript_self.property("javaScriptConsoleMessage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("javaScriptConsoleMessage") & QScriptValue::QObjectMember)) {
        QWebPage::javaScriptConsoleMessage(message, lineNumber, sourceID);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, message)
            << qScriptValueFromValue(_q_engine, lineNumber)
            << qScriptValueFromValue(_q_engine, sourceID));
    }
}

bool  QtScriptShell_QWebPage::javaScriptPrompt(QWebFrame*  originatingFrame, const QString&  msg, const QString&  defaultValue, QString*  result)
{
    QScriptValue _q_function = __qtscript_self.property("javaScriptPrompt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("javaScriptPrompt") & QScriptValue::QObjectMember)) {
        return QWebPage::javaScriptPrompt(originatingFrame, msg, defaultValue, result);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, originatingFrame)
            << qScriptValueFromValue(_q_engine, msg)
            << qScriptValueFromValue(_q_engine, defaultValue)
            << qScriptValueFromValue(_q_engine, result)));
    }
}

bool  QtScriptShell_QWebPage::shouldInterruptJavaScript()
{
    QScriptValue _q_function = __qtscript_self.property("shouldInterruptJavaScript");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("shouldInterruptJavaScript") & QScriptValue::QObjectMember)) {
        return QWebPage::shouldInterruptJavaScript();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QWebPage::supportsExtension(QWebPage::Extension  extension) const
{
    QScriptValue _q_function = __qtscript_self.property("supportsExtension");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportsExtension") & QScriptValue::QObjectMember)) {
        return QWebPage::supportsExtension(extension);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, extension)));
    }
}

void QtScriptShell_QWebPage::triggerAction(QWebPage::WebAction  action, bool  checked)
{
    QScriptValue _q_function = __qtscript_self.property("triggerAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("triggerAction") & QScriptValue::QObjectMember)) {
        QWebPage::triggerAction(action, checked);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, checked));
    }
}

QString  QtScriptShell_QWebPage::userAgentForUrl(const QUrl&  url) const
{
    QScriptValue _q_function = __qtscript_self.property("userAgentForUrl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("userAgentForUrl") & QScriptValue::QObjectMember)) {
        return QWebPage::userAgentForUrl(url);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
    }
}

