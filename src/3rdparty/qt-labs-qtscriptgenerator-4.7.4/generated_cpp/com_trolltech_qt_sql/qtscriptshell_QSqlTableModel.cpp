#include "qtscriptshell_QSqlTableModel.h"

#include <QtScript/QScriptEngine>
#include <QSize>
#include <QSqlIndex>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlindex.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QSqlRecord)
template <> \
struct QMetaTypeId< QMap<int,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QMap<int,QVariant> >("QMap<int,QVariant>"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QSqlTableModel::EditStrategy)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QSqlTableModel::QtScriptShell_QSqlTableModel(QObject*  parent, QSqlDatabase  db)
    : QSqlTableModel(parent, db) {}

QtScriptShell_QSqlTableModel::~QtScriptShell_QSqlTableModel() {}

QModelIndex  QtScriptShell_QSqlTableModel::buddy(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("buddy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("buddy") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::buddy(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QSqlTableModel::canFetchMore(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canFetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canFetchMore") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::canFetchMore(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QSqlTableModel::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QSqlTableModel::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QSqlTableModel::clear()
{
    QScriptValue _q_function = __qtscript_self.property("clear");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clear") & QScriptValue::QObjectMember)) {
        QSqlTableModel::clear();
    } else {
        _q_function.call(__qtscript_self);
    }
}

int  QtScriptShell_QSqlTableModel::columnCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("columnCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnCount") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::columnCount(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QSqlTableModel::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QSqlTableModel::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QVariant  QtScriptShell_QSqlTableModel::data(const QModelIndex&  idx, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::data(idx, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, idx)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

bool  QtScriptShell_QSqlTableModel::deleteRowFromTable(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("deleteRowFromTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("deleteRowFromTable") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::deleteRowFromTable(row);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
    }
}

bool  QtScriptShell_QSqlTableModel::dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("dropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropMimeData") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::dropMimeData(data, action, row, column, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QMimeData *>(data))
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlTableModel::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QSqlTableModel::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

void QtScriptShell_QSqlTableModel::fetchMore(const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("fetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchMore") & QScriptValue::QObjectMember)) {
        QSqlTableModel::fetchMore(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent));
    }
}

Qt::ItemFlags  QtScriptShell_QSqlTableModel::flags(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("flags");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("flags") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::flags(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<Qt::ItemFlags >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

QVariant  QtScriptShell_QSqlTableModel::headerData(int  section, Qt::Orientation  orientation, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("headerData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("headerData") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::headerData(section, orientation, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, section)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

QModelIndex  QtScriptShell_QSqlTableModel::index(int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("index");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("index") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::index(row, column, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlTableModel::insertColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertColumns") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::insertColumns(column, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlTableModel::insertRowIntoTable(const QSqlRecord&  values)
{
    QScriptValue _q_function = __qtscript_self.property("insertRowIntoTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRowIntoTable") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::insertRowIntoTable(values);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, values)));
    }
}

bool  QtScriptShell_QSqlTableModel::insertRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRows") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::insertRows(row, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QMap<int , QVariant >  QtScriptShell_QSqlTableModel::itemData(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("itemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemData") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::itemData(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QMap<int , QVariant > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

QList<QModelIndex >  QtScriptShell_QSqlTableModel::match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const
{
    QScriptValue _q_function = __qtscript_self.property("match");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("match") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::match(start, role, value, hits, flags);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QList<QModelIndex > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, start)
            << qScriptValueFromValue(_q_engine, role)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, hits)
            << qScriptValueFromValue(_q_engine, flags)));
    }
}

QMimeData*  QtScriptShell_QSqlTableModel::mimeData(const QList<QModelIndex >&  indexes) const
{
    QScriptValue _q_function = __qtscript_self.property("mimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeData") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::mimeData(indexes);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QMimeData* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, indexes)));
    }
}

QStringList  QtScriptShell_QSqlTableModel::mimeTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("mimeTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeTypes") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::mimeTypes();
    } else {
        return qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self));
    }
}

QString  QtScriptShell_QSqlTableModel::orderByClause() const
{
    QScriptValue _q_function = __qtscript_self.property("orderByClause");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("orderByClause") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::orderByClause();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QSqlTableModel::queryChange()
{
    QScriptValue _q_function = __qtscript_self.property("queryChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("queryChange") & QScriptValue::QObjectMember)) {
        QSqlTableModel::queryChange();
    } else {
        _q_function.call(__qtscript_self);
    }
}

bool  QtScriptShell_QSqlTableModel::removeColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeColumns") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::removeColumns(column, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlTableModel::removeRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeRows") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::removeRows(row, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QSqlTableModel::revert()
{
    QScriptValue _q_function = __qtscript_self.property("revert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revert") & QScriptValue::QObjectMember)) {
        QSqlTableModel::revert();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QSqlTableModel::revertRow(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("revertRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revertRow") & QScriptValue::QObjectMember)) {
        QSqlTableModel::revertRow(row);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row));
    }
}

int  QtScriptShell_QSqlTableModel::rowCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("rowCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowCount") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::rowCount(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlTableModel::select()
{
    QScriptValue _q_function = __qtscript_self.property("select");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("select") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::select();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QString  QtScriptShell_QSqlTableModel::selectStatement() const
{
    QScriptValue _q_function = __qtscript_self.property("selectStatement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectStatement") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::selectStatement();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlTableModel::setData(const QModelIndex&  index, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::setData(index, value, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

void QtScriptShell_QSqlTableModel::setEditStrategy(QSqlTableModel::EditStrategy  strategy)
{
    QScriptValue _q_function = __qtscript_self.property("setEditStrategy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEditStrategy") & QScriptValue::QObjectMember)) {
        QSqlTableModel::setEditStrategy(strategy);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, strategy));
    }
}

void QtScriptShell_QSqlTableModel::setFilter(const QString&  filter)
{
    QScriptValue _q_function = __qtscript_self.property("setFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFilter") & QScriptValue::QObjectMember)) {
        QSqlTableModel::setFilter(filter);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, filter));
    }
}

bool  QtScriptShell_QSqlTableModel::setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setHeaderData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setHeaderData") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::setHeaderData(section, orientation, value, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, section)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

bool  QtScriptShell_QSqlTableModel::setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("setItemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setItemData") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::setItemData(index, roles);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, roles)));
    }
}

void QtScriptShell_QSqlTableModel::setSort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("setSort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSort") & QScriptValue::QObjectMember)) {
        QSqlTableModel::setSort(column, order);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, order));
    }
}

void QtScriptShell_QSqlTableModel::setTable(const QString&  tableName)
{
    QScriptValue _q_function = __qtscript_self.property("setTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setTable") & QScriptValue::QObjectMember)) {
        QSqlTableModel::setTable(tableName);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, tableName));
    }
}

void QtScriptShell_QSqlTableModel::sort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("sort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sort") & QScriptValue::QObjectMember)) {
        QSqlTableModel::sort(column, order);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, order));
    }
}

QSize  QtScriptShell_QSqlTableModel::span(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("span");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("span") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::span(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QSqlTableModel::submit()
{
    QScriptValue _q_function = __qtscript_self.property("submit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("submit") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::submit();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

Qt::DropActions  QtScriptShell_QSqlTableModel::supportedDropActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDropActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDropActions") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::supportedDropActions();
    } else {
        return qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QSqlTableModel::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QSqlTableModel::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QSqlTableModel::updateRowInTable(int  row, const QSqlRecord&  values)
{
    QScriptValue _q_function = __qtscript_self.property("updateRowInTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateRowInTable") & QScriptValue::QObjectMember)) {
        return QSqlTableModel::updateRowInTable(row, values);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, values)));
    }
}

