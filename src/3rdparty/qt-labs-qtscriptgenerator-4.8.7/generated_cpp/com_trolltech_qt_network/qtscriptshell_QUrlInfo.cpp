#include "qtscriptshell_QUrlInfo.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qdatetime.h>
#include <qurl.h>
#include <qurlinfo.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QUrlInfo::QtScriptShell_QUrlInfo()
    : QUrlInfo() {}

QtScriptShell_QUrlInfo::QtScriptShell_QUrlInfo(const QString&  name, int  permissions, const QString&  owner, const QString&  group, qint64  size, const QDateTime&  lastModified, const QDateTime&  lastRead, bool  isDir, bool  isFile, bool  isSymLink, bool  isWritable, bool  isReadable, bool  isExecutable)
    : QUrlInfo(name, permissions, owner, group, size, lastModified, lastRead, isDir, isFile, isSymLink, isWritable, isReadable, isExecutable) {}

QtScriptShell_QUrlInfo::QtScriptShell_QUrlInfo(const QUrl&  url, int  permissions, const QString&  owner, const QString&  group, qint64  size, const QDateTime&  lastModified, const QDateTime&  lastRead, bool  isDir, bool  isFile, bool  isSymLink, bool  isWritable, bool  isReadable, bool  isExecutable)
    : QUrlInfo(url, permissions, owner, group, size, lastModified, lastRead, isDir, isFile, isSymLink, isWritable, isReadable, isExecutable) {}

QtScriptShell_QUrlInfo::QtScriptShell_QUrlInfo(const QUrlInfo&  ui)
    : QUrlInfo(ui) {}

QtScriptShell_QUrlInfo::~QtScriptShell_QUrlInfo() {}

void QtScriptShell_QUrlInfo::setDir(bool  b)
{
    QScriptValue _q_function = __qtscript_self.property("setDir");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setDir") & QScriptValue::QObjectMember)) {
        QUrlInfo::setDir(b);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, b));
    }
}

void QtScriptShell_QUrlInfo::setFile(bool  b)
{
    QScriptValue _q_function = __qtscript_self.property("setFile");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFile") & QScriptValue::QObjectMember)) {
        QUrlInfo::setFile(b);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, b));
    }
}

void QtScriptShell_QUrlInfo::setGroup(const QString&  s)
{
    QScriptValue _q_function = __qtscript_self.property("setGroup");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGroup") & QScriptValue::QObjectMember)) {
        QUrlInfo::setGroup(s);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, s));
    }
}

void QtScriptShell_QUrlInfo::setLastModified(const QDateTime&  dt)
{
    QScriptValue _q_function = __qtscript_self.property("setLastModified");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setLastModified") & QScriptValue::QObjectMember)) {
        QUrlInfo::setLastModified(dt);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, dt));
    }
}

void QtScriptShell_QUrlInfo::setName(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("setName");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setName") & QScriptValue::QObjectMember)) {
        QUrlInfo::setName(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name));
    }
}

void QtScriptShell_QUrlInfo::setOwner(const QString&  s)
{
    QScriptValue _q_function = __qtscript_self.property("setOwner");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setOwner") & QScriptValue::QObjectMember)) {
        QUrlInfo::setOwner(s);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, s));
    }
}

void QtScriptShell_QUrlInfo::setPermissions(int  p)
{
    QScriptValue _q_function = __qtscript_self.property("setPermissions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setPermissions") & QScriptValue::QObjectMember)) {
        QUrlInfo::setPermissions(p);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, p));
    }
}

void QtScriptShell_QUrlInfo::setReadable(bool  b)
{
    QScriptValue _q_function = __qtscript_self.property("setReadable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setReadable") & QScriptValue::QObjectMember)) {
        QUrlInfo::setReadable(b);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, b));
    }
}

void QtScriptShell_QUrlInfo::setSize(qint64  size)
{
    QScriptValue _q_function = __qtscript_self.property("setSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSize") & QScriptValue::QObjectMember)) {
        QUrlInfo::setSize(size);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, size));
    }
}

void QtScriptShell_QUrlInfo::setSymLink(bool  b)
{
    QScriptValue _q_function = __qtscript_self.property("setSymLink");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSymLink") & QScriptValue::QObjectMember)) {
        QUrlInfo::setSymLink(b);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, b));
    }
}

void QtScriptShell_QUrlInfo::setWritable(bool  b)
{
    QScriptValue _q_function = __qtscript_self.property("setWritable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setWritable") & QScriptValue::QObjectMember)) {
        QUrlInfo::setWritable(b);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, b));
    }
}

