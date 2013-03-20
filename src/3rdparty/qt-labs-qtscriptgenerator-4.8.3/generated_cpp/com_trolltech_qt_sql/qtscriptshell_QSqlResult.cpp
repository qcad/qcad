#include "qtscriptshell_QSqlResult.h"

#include <QtScript/QScriptEngine>
#include <QSize>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlrecord.h>
#include <qsqlresult.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QFlags<QSql::ParamTypeFlag>)
Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSqlError)

QtScriptShell_QSqlResult::QtScriptShell_QSqlResult(const QSqlDriver*  db)
    : QSqlResult(db) {}

QtScriptShell_QSqlResult::~QtScriptShell_QSqlResult() {}

void QtScriptShell_QSqlResult::bindValue(const QString&  placeholder, const QVariant&  val, QSql::ParamType  type)
{
    QScriptValue _q_function = __qtscript_self.property("bindValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bindValue") & QScriptValue::QObjectMember)) {
        QSqlResult::bindValue(placeholder, val, type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, placeholder)
            << qScriptValueFromValue(_q_engine, val)
            << qScriptValueFromValue(_q_engine, type));
    }
}

void QtScriptShell_QSqlResult::bindValue(int  pos, const QVariant&  val, QSql::ParamType  type)
{
    QScriptValue _q_function = __qtscript_self.property("bindValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bindValue") & QScriptValue::QObjectMember)) {
        QSqlResult::bindValue(pos, val, type);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pos)
            << qScriptValueFromValue(_q_engine, val)
            << qScriptValueFromValue(_q_engine, type));
    }
}

QVariant  QtScriptShell_QSqlResult::data(int  i)
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::data() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, i)));
    }
}

bool  QtScriptShell_QSqlResult::exec()
{
    QScriptValue _q_function = __qtscript_self.property("exec");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("exec") & QScriptValue::QObjectMember)) {
        return QSqlResult::exec();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlResult::fetch(int  i)
{
    QScriptValue _q_function = __qtscript_self.property("fetch");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetch") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::fetch() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, i)));
    }
}

bool  QtScriptShell_QSqlResult::fetchFirst()
{
    QScriptValue _q_function = __qtscript_self.property("fetchFirst");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchFirst") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::fetchFirst() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlResult::fetchLast()
{
    QScriptValue _q_function = __qtscript_self.property("fetchLast");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchLast") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::fetchLast() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlResult::fetchNext()
{
    QScriptValue _q_function = __qtscript_self.property("fetchNext");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchNext") & QScriptValue::QObjectMember)) {
        return QSqlResult::fetchNext();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlResult::fetchPrevious()
{
    QScriptValue _q_function = __qtscript_self.property("fetchPrevious");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchPrevious") & QScriptValue::QObjectMember)) {
        return QSqlResult::fetchPrevious();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QVariant  QtScriptShell_QSqlResult::handle() const
{
    QScriptValue _q_function = __qtscript_self.property("handle");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("handle") & QScriptValue::QObjectMember)) {
        return QSqlResult::handle();
    } else {
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlResult::isNull(int  i)
{
    QScriptValue _q_function = __qtscript_self.property("isNull");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isNull") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::isNull() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, i)));
    }
}

QVariant  QtScriptShell_QSqlResult::lastInsertId() const
{
    QScriptValue _q_function = __qtscript_self.property("lastInsertId");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lastInsertId") & QScriptValue::QObjectMember)) {
        return QSqlResult::lastInsertId();
    } else {
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QSqlResult::numRowsAffected()
{
    QScriptValue _q_function = __qtscript_self.property("numRowsAffected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("numRowsAffected") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::numRowsAffected() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlResult::prepare(const QString&  query)
{
    QScriptValue _q_function = __qtscript_self.property("prepare");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("prepare") & QScriptValue::QObjectMember)) {
        return QSqlResult::prepare(query);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query)));
    }
}

QSqlRecord  QtScriptShell_QSqlResult::record() const
{
    QScriptValue _q_function = __qtscript_self.property("record");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("record") & QScriptValue::QObjectMember)) {
        return QSqlResult::record();
    } else {
        return qscriptvalue_cast<QSqlRecord >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlResult::reset(const QString&  sqlquery)
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::reset() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sqlquery)));
    }
}

bool  QtScriptShell_QSqlResult::savePrepare(const QString&  sqlquery)
{
    QScriptValue _q_function = __qtscript_self.property("savePrepare");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("savePrepare") & QScriptValue::QObjectMember)) {
        return QSqlResult::savePrepare(sqlquery);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sqlquery)));
    }
}

void QtScriptShell_QSqlResult::setActive(bool  a)
{
    QScriptValue _q_function = __qtscript_self.property("setActive");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setActive") & QScriptValue::QObjectMember)) {
        QSqlResult::setActive(a);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, a));
    }
}

void QtScriptShell_QSqlResult::setAt(int  at)
{
    QScriptValue _q_function = __qtscript_self.property("setAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setAt") & QScriptValue::QObjectMember)) {
        QSqlResult::setAt(at);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, at));
    }
}

void QtScriptShell_QSqlResult::setForwardOnly(bool  forward)
{
    QScriptValue _q_function = __qtscript_self.property("setForwardOnly");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setForwardOnly") & QScriptValue::QObjectMember)) {
        QSqlResult::setForwardOnly(forward);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, forward));
    }
}

void QtScriptShell_QSqlResult::setLastError(const QSqlError&  e)
{
    QScriptValue _q_function = __qtscript_self.property("setLastError");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setLastError") & QScriptValue::QObjectMember)) {
        QSqlResult::setLastError(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

void QtScriptShell_QSqlResult::setQuery(const QString&  query)
{
    QScriptValue _q_function = __qtscript_self.property("setQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setQuery") & QScriptValue::QObjectMember)) {
        QSqlResult::setQuery(query);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query));
    }
}

void QtScriptShell_QSqlResult::setSelect(bool  s)
{
    QScriptValue _q_function = __qtscript_self.property("setSelect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelect") & QScriptValue::QObjectMember)) {
        QSqlResult::setSelect(s);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, s));
    }
}

int  QtScriptShell_QSqlResult::size()
{
    QScriptValue _q_function = __qtscript_self.property("size");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("size") & QScriptValue::QObjectMember)) {
        qFatal("QSqlResult::size() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

