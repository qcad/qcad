#include "qtscriptshell_QNetworkDiskCache.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractnetworkcache.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qnetworkdiskcache.h>
#include <qobject.h>
#include <qurl.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QNetworkCacheMetaData)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QNetworkDiskCache::QtScriptShell_QNetworkDiskCache(QObject*  parent)
    : QNetworkDiskCache(parent) {}

QtScriptShell_QNetworkDiskCache::~QtScriptShell_QNetworkDiskCache() {}

qint64  QtScriptShell_QNetworkDiskCache::cacheSize() const
{
    QScriptValue _q_function = __qtscript_self.property("cacheSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("cacheSize") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::cacheSize();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QNetworkDiskCache::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QNetworkDiskCache::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QNetworkDiskCache::clear()
{
    QScriptValue _q_function = __qtscript_self.property("clear");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clear") & QScriptValue::QObjectMember)) {
        QNetworkDiskCache::clear();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QNetworkDiskCache::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QNetworkDiskCache::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QIODevice*  QtScriptShell_QNetworkDiskCache::data(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::data(url);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QIODevice* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
    }
}

bool  QtScriptShell_QNetworkDiskCache::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QNetworkDiskCache::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

qint64  QtScriptShell_QNetworkDiskCache::expire()
{
    QScriptValue _q_function = __qtscript_self.property("expire");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("expire") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::expire();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QNetworkDiskCache::insert(QIODevice*  device)
{
    QScriptValue _q_function = __qtscript_self.property("insert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insert") & QScriptValue::QObjectMember)) {
        QNetworkDiskCache::insert(device);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, device));
    }
}

QNetworkCacheMetaData  QtScriptShell_QNetworkDiskCache::metaData(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("metaData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metaData") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::metaData(url);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QNetworkCacheMetaData >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
    }
}

QIODevice*  QtScriptShell_QNetworkDiskCache::prepare(const QNetworkCacheMetaData&  metaData)
{
    QScriptValue _q_function = __qtscript_self.property("prepare");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("prepare") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::prepare(metaData);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QIODevice* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metaData)));
    }
}

bool  QtScriptShell_QNetworkDiskCache::remove(const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("remove");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("remove") & QScriptValue::QObjectMember)) {
        return QNetworkDiskCache::remove(url);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
    }
}

void QtScriptShell_QNetworkDiskCache::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QNetworkDiskCache::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QNetworkDiskCache::updateMetaData(const QNetworkCacheMetaData&  metaData)
{
    QScriptValue _q_function = __qtscript_self.property("updateMetaData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateMetaData") & QScriptValue::QObjectMember)) {
        QNetworkDiskCache::updateMetaData(metaData);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metaData));
    }
}

