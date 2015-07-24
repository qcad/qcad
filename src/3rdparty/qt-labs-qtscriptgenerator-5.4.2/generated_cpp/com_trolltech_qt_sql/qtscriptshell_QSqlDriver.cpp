#include "qtscriptshell_QSqlDriver.h"

#include <QtScript/QScriptEngine>
#include <QSize>
#include <QSqlError>
#include <QSqlIndex>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlfield.h>
#include <qsqlindex.h>
#include <qsqlrecord.h>
#include <qsqlresult.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QSqlResult*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QSqlDriver::IdentifierType)
Q_DECLARE_METATYPE(QSqlField)
Q_DECLARE_METATYPE(QSqlDriver::DriverFeature)
Q_DECLARE_METATYPE(QSqlIndex)
Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSqlDriver::StatementType)
Q_DECLARE_METATYPE(QSql::TableType)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QSqlDriver::QtScriptShell_QSqlDriver(QObject*  parent)
    : QSqlDriver(parent) {}

QtScriptShell_QSqlDriver::~QtScriptShell_QSqlDriver() {}

bool  QtScriptShell_QSqlDriver::beginTransaction()
{
    QScriptValue _q_function = __qtscript_self.property("beginTransaction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("beginTransaction") & QScriptValue::QObjectMember)) {
        return QSqlDriver::beginTransaction();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlDriver::cancelQuery()
{
    QScriptValue _q_function = __qtscript_self.property("cancelQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("cancelQuery") & QScriptValue::QObjectMember)) {
        return QSqlDriver::cancelQuery();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QSqlDriver::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QSqlDriver::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QSqlDriver::close()
{
    QScriptValue _q_function = __qtscript_self.property("close");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("close") & QScriptValue::QObjectMember)) {
        qFatal("QSqlDriver::close() is abstract!");
    } else {
        _q_function.call(__qtscript_self);
    }
}

bool  QtScriptShell_QSqlDriver::commitTransaction()
{
    QScriptValue _q_function = __qtscript_self.property("commitTransaction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("commitTransaction") & QScriptValue::QObjectMember)) {
        return QSqlDriver::commitTransaction();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QSqlResult*  QtScriptShell_QSqlDriver::createResult() const
{
    QScriptValue _q_function = __qtscript_self.property("createResult");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createResult") & QScriptValue::QObjectMember)) {
        qFatal("QSqlDriver::createResult() is abstract!");
    } else {
        return qscriptvalue_cast<QSqlResult* >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QSqlDriver::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QSqlDriver::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QString  QtScriptShell_QSqlDriver::escapeIdentifier(const QString&  identifier, QSqlDriver::IdentifierType  type) const
{
    QScriptValue _q_function = __qtscript_self.property("escapeIdentifier");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("escapeIdentifier") & QScriptValue::QObjectMember)) {
        return QSqlDriver::escapeIdentifier(identifier, type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, identifier)
            << qScriptValueFromValue(_q_engine, type)));
    }
}

bool  QtScriptShell_QSqlDriver::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QSqlDriver::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QSqlDriver::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QSqlDriver::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

QString  QtScriptShell_QSqlDriver::formatValue(const QSqlField&  field, bool  trimStrings) const
{
    QScriptValue _q_function = __qtscript_self.property("formatValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("formatValue") & QScriptValue::QObjectMember)) {
        return QSqlDriver::formatValue(field, trimStrings);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, field)
            << qScriptValueFromValue(_q_engine, trimStrings)));
    }
}

QVariant  QtScriptShell_QSqlDriver::handle() const
{
    QScriptValue _q_function = __qtscript_self.property("handle");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("handle") & QScriptValue::QObjectMember)) {
        return QSqlDriver::handle();
    } else {
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlDriver::hasFeature(QSqlDriver::DriverFeature  f) const
{
    QScriptValue _q_function = __qtscript_self.property("hasFeature");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasFeature") & QScriptValue::QObjectMember)) {
        qFatal("QSqlDriver::hasFeature() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, f)));
    }
}

bool  QtScriptShell_QSqlDriver::isIdentifierEscaped(const QString&  identifier, QSqlDriver::IdentifierType  type) const
{
    QScriptValue _q_function = __qtscript_self.property("isIdentifierEscaped");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isIdentifierEscaped") & QScriptValue::QObjectMember)) {
        return QSqlDriver::isIdentifierEscaped(identifier, type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, identifier)
            << qScriptValueFromValue(_q_engine, type)));
    }
}

bool  QtScriptShell_QSqlDriver::isOpen() const
{
    QScriptValue _q_function = __qtscript_self.property("isOpen");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isOpen") & QScriptValue::QObjectMember)) {
        return QSqlDriver::isOpen();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlDriver::open(const QString&  db, const QString&  user, const QString&  password, const QString&  host, int  port, const QString&  connOpts)
{
    QScriptValue _q_function = __qtscript_self.property("open");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("open") & QScriptValue::QObjectMember)) {
        qFatal("QSqlDriver::open() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, db)
            << qScriptValueFromValue(_q_engine, user)
            << qScriptValueFromValue(_q_engine, password)
            << qScriptValueFromValue(_q_engine, host)
            << qScriptValueFromValue(_q_engine, port)
            << qScriptValueFromValue(_q_engine, connOpts)));
    }
}

QSqlIndex  QtScriptShell_QSqlDriver::primaryIndex(const QString&  tableName) const
{
    QScriptValue _q_function = __qtscript_self.property("primaryIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("primaryIndex") & QScriptValue::QObjectMember)) {
        return QSqlDriver::primaryIndex(tableName);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSqlIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, tableName)));
    }
}

QSqlRecord  QtScriptShell_QSqlDriver::record(const QString&  tableName) const
{
    QScriptValue _q_function = __qtscript_self.property("record");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("record") & QScriptValue::QObjectMember)) {
        return QSqlDriver::record(tableName);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSqlRecord >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, tableName)));
    }
}

bool  QtScriptShell_QSqlDriver::rollbackTransaction()
{
    QScriptValue _q_function = __qtscript_self.property("rollbackTransaction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rollbackTransaction") & QScriptValue::QObjectMember)) {
        return QSqlDriver::rollbackTransaction();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QSqlDriver::setLastError(const QSqlError&  e)
{
    QScriptValue _q_function = __qtscript_self.property("setLastError");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setLastError") & QScriptValue::QObjectMember)) {
        QSqlDriver::setLastError(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QSqlDriver::setOpen(bool  o)
{
    QScriptValue _q_function = __qtscript_self.property("setOpen");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setOpen") & QScriptValue::QObjectMember)) {
        QSqlDriver::setOpen(o);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, o));
    }
}

void QtScriptShell_QSqlDriver::setOpenError(bool  e)
{
    QScriptValue _q_function = __qtscript_self.property("setOpenError");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setOpenError") & QScriptValue::QObjectMember)) {
        QSqlDriver::setOpenError(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

QString  QtScriptShell_QSqlDriver::sqlStatement(QSqlDriver::StatementType  type, const QString&  tableName, const QSqlRecord&  rec, bool  preparedStatement) const
{
    QScriptValue _q_function = __qtscript_self.property("sqlStatement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sqlStatement") & QScriptValue::QObjectMember)) {
        return QSqlDriver::sqlStatement(type, tableName, rec, preparedStatement);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, type)
            << qScriptValueFromValue(_q_engine, tableName)
            << qScriptValueFromValue(_q_engine, rec)
            << qScriptValueFromValue(_q_engine, preparedStatement)));
    }
}

QString  QtScriptShell_QSqlDriver::stripDelimiters(const QString&  identifier, QSqlDriver::IdentifierType  type) const
{
    QScriptValue _q_function = __qtscript_self.property("stripDelimiters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("stripDelimiters") & QScriptValue::QObjectMember)) {
        return QSqlDriver::stripDelimiters(identifier, type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, identifier)
            << qScriptValueFromValue(_q_engine, type)));
    }
}

bool  QtScriptShell_QSqlDriver::subscribeToNotification(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("subscribeToNotification");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subscribeToNotification") & QScriptValue::QObjectMember)) {
        return QSqlDriver::subscribeToNotification(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

QStringList  QtScriptShell_QSqlDriver::subscribedToNotifications() const
{
    QScriptValue _q_function = __qtscript_self.property("subscribedToNotifications");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subscribedToNotifications") & QScriptValue::QObjectMember)) {
        return QSqlDriver::subscribedToNotifications();
    } else {
        return qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self));
    }
}

QStringList  QtScriptShell_QSqlDriver::tables(QSql::TableType  tableType) const
{
    QScriptValue _q_function = __qtscript_self.property("tables");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("tables") & QScriptValue::QObjectMember)) {
        return QSqlDriver::tables(tableType);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, tableType)));
    }
}

void QtScriptShell_QSqlDriver::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QSqlDriver::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QSqlDriver::unsubscribeFromNotification(const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("unsubscribeFromNotification");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unsubscribeFromNotification") & QScriptValue::QObjectMember)) {
        return QSqlDriver::unsubscribeFromNotification(name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, name)));
    }
}

