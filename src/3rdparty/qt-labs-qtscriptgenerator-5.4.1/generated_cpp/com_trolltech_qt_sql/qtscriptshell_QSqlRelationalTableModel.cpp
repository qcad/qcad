#include "qtscriptshell_QSqlRelationalTableModel.h"

#include <QtScript/QScriptEngine>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlindex.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qsqlrelationaltablemodel.h>
#include <qsqltablemodel.h>
#include <qstringlist.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(const QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QSqlRecord)
template <> \
struct QMetaTypeId< QMap<int,QVariant > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QMap<int,QVariant > >("QMap<int,QVariant >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QList<QModelIndex >)
Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(QSqlTableModel*)
template <> \
struct QMetaTypeId< QHash<int,QByteArray > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QHash<int,QByteArray > >("QHash<int,QByteArray >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(QSqlTableModel::EditStrategy)
Q_DECLARE_METATYPE(QSqlRelation)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QSqlRelationalTableModel::QtScriptShell_QSqlRelationalTableModel(QObject*  parent, QSqlDatabase  db)
    : QSqlRelationalTableModel(parent, db) {}

QtScriptShell_QSqlRelationalTableModel::~QtScriptShell_QSqlRelationalTableModel() {}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::buddy(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("buddy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("buddy") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::buddy(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::canDropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canDropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canDropMimeData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::canDropMimeData(data, action, row, column, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const QMimeData *>(data))
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::canFetchMore(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canFetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canFetchMore") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::canFetchMore(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QSqlRelationalTableModel::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QSqlRelationalTableModel::clear()
{
    QScriptValue _q_function = __qtscript_self.property("clear");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clear") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::clear();
    } else {
        _q_function.call(__qtscript_self);
    }
}

int  QtScriptShell_QSqlRelationalTableModel::columnCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("columnCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnCount") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::columnCount(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QSqlRelationalTableModel::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QVariant  QtScriptShell_QSqlRelationalTableModel::data(const QModelIndex&  item, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::data(item, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, item)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::deleteRowFromTable(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("deleteRowFromTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("deleteRowFromTable") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::deleteRowFromTable(row);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("dropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropMimeData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::dropMimeData(data, action, row, column, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const QMimeData *>(data))
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

void QtScriptShell_QSqlRelationalTableModel::fetchMore(const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("fetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchMore") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::fetchMore(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent));
    }
}

Qt::ItemFlags  QtScriptShell_QSqlRelationalTableModel::flags(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("flags");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("flags") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::flags(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<Qt::ItemFlags >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

QVariant  QtScriptShell_QSqlRelationalTableModel::headerData(int  section, Qt::Orientation  orientation, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("headerData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("headerData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::headerData(section, orientation, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, section)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::index(int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("index");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("index") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::index(row, column, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::indexInQuery(const QModelIndex&  item) const
{
    QScriptValue _q_function = __qtscript_self.property("indexInQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexInQuery") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::indexInQuery(item);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, item)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::insertColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertColumns") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::insertColumns(column, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::insertRowIntoTable(const QSqlRecord&  values)
{
    QScriptValue _q_function = __qtscript_self.property("insertRowIntoTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRowIntoTable") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::insertRowIntoTable(values);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, values)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::insertRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRows") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::insertRows(row, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QMap<int , QVariant >  QtScriptShell_QSqlRelationalTableModel::itemData(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("itemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::itemData(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QMap<int , QVariant > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

QList<QModelIndex >  QtScriptShell_QSqlRelationalTableModel::match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const
{
    QScriptValue _q_function = __qtscript_self.property("match");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("match") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::match(start, role, value, hits, flags);
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

QMimeData*  QtScriptShell_QSqlRelationalTableModel::mimeData(const QList<QModelIndex >&  indexes) const
{
    QScriptValue _q_function = __qtscript_self.property("mimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::mimeData(indexes);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QMimeData* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, indexes)));
    }
}

QStringList  QtScriptShell_QSqlRelationalTableModel::mimeTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("mimeTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeTypes") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::mimeTypes();
    } else {
        return qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::moveColumns(const QModelIndex&  sourceParent, int  sourceColumn, int  count, const QModelIndex&  destinationParent, int  destinationChild)
{
    QScriptValue _q_function = __qtscript_self.property("moveColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveColumns") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::moveColumns(sourceParent, sourceColumn, count, destinationParent, destinationChild);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sourceParent)
            << qScriptValueFromValue(_q_engine, sourceColumn)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, destinationParent)
            << qScriptValueFromValue(_q_engine, destinationChild)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::moveRows(const QModelIndex&  sourceParent, int  sourceRow, int  count, const QModelIndex&  destinationParent, int  destinationChild)
{
    QScriptValue _q_function = __qtscript_self.property("moveRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveRows") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::moveRows(sourceParent, sourceRow, count, destinationParent, destinationChild);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sourceParent)
            << qScriptValueFromValue(_q_engine, sourceRow)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, destinationParent)
            << qScriptValueFromValue(_q_engine, destinationChild)));
    }
}

QString  QtScriptShell_QSqlRelationalTableModel::orderByClause() const
{
    QScriptValue _q_function = __qtscript_self.property("orderByClause");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("orderByClause") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::orderByClause();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QSqlRelationalTableModel::queryChange()
{
    QScriptValue _q_function = __qtscript_self.property("queryChange");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("queryChange") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::queryChange();
    } else {
        _q_function.call(__qtscript_self);
    }
}

QSqlTableModel*  QtScriptShell_QSqlRelationalTableModel::relationModel(int  column) const
{
    QScriptValue _q_function = __qtscript_self.property("relationModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relationModel") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::relationModel(column);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSqlTableModel* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::removeColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeColumns") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::removeColumns(column, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::removeRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeRows") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::removeRows(row, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QSqlRelationalTableModel::revert()
{
    QScriptValue _q_function = __qtscript_self.property("revert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revert") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::revert();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QSqlRelationalTableModel::revertRow(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("revertRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revertRow") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::revertRow(row);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row));
    }
}

QHash<int , QByteArray >  QtScriptShell_QSqlRelationalTableModel::roleNames() const
{
    QScriptValue _q_function = __qtscript_self.property("roleNames");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("roleNames") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::roleNames();
    } else {
        return qscriptvalue_cast<QHash<int , QByteArray > >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QSqlRelationalTableModel::rowCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("rowCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowCount") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::rowCount(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::select()
{
    QScriptValue _q_function = __qtscript_self.property("select");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("select") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::select();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::selectRow(int  row)
{
    QScriptValue _q_function = __qtscript_self.property("selectRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectRow") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::selectRow(row);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
    }
}

QString  QtScriptShell_QSqlRelationalTableModel::selectStatement() const
{
    QScriptValue _q_function = __qtscript_self.property("selectStatement");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectStatement") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::selectStatement();
    } else {
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::setData(const QModelIndex&  item, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::setData(item, value, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, item)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setEditStrategy(QSqlTableModel::EditStrategy  strategy)
{
    QScriptValue _q_function = __qtscript_self.property("setEditStrategy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEditStrategy") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::setEditStrategy(strategy);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, strategy));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setFilter(const QString&  filter)
{
    QScriptValue _q_function = __qtscript_self.property("setFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFilter") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::setFilter(filter);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, filter));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setHeaderData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setHeaderData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::setHeaderData(section, orientation, value, role);
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

bool  QtScriptShell_QSqlRelationalTableModel::setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("setItemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setItemData") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::setItemData(index, roles);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, roles)));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setRelation(int  column, const QSqlRelation&  relation)
{
    QScriptValue _q_function = __qtscript_self.property("setRelation");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRelation") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::setRelation(column, relation);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, relation));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setSort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("setSort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSort") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::setSort(column, order);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, order));
    }
}

void QtScriptShell_QSqlRelationalTableModel::setTable(const QString&  tableName)
{
    QScriptValue _q_function = __qtscript_self.property("setTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setTable") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::setTable(tableName);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, tableName));
    }
}

QModelIndex  QtScriptShell_QSqlRelationalTableModel::sibling(int  row, int  column, const QModelIndex&  idx) const
{
    QScriptValue _q_function = __qtscript_self.property("sibling");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sibling") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::sibling(row, column, idx);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, idx)));
    }
}

void QtScriptShell_QSqlRelationalTableModel::sort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("sort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sort") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::sort(column, order);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, order));
    }
}

QSize  QtScriptShell_QSqlRelationalTableModel::span(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("span");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("span") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::span(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::submit()
{
    QScriptValue _q_function = __qtscript_self.property("submit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("submit") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::submit();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

Qt::DropActions  QtScriptShell_QSqlRelationalTableModel::supportedDragActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDragActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDragActions") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::supportedDragActions();
    } else {
        return qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
    }
}

Qt::DropActions  QtScriptShell_QSqlRelationalTableModel::supportedDropActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDropActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDropActions") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::supportedDropActions();
    } else {
        return qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QSqlRelationalTableModel::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QSqlRelationalTableModel::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QSqlRelationalTableModel::updateRowInTable(int  row, const QSqlRecord&  values)
{
    QScriptValue _q_function = __qtscript_self.property("updateRowInTable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateRowInTable") & QScriptValue::QObjectMember)) {
        return QSqlRelationalTableModel::updateRowInTable(row, values);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, values)));
    }
}

