#include "qtscriptshell_QAbstractProxyModel.h"

#include <QtScript/QScriptEngine>
#include <QItemSelection>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractproxymodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qitemselectionmodel.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::Orientation)
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
Q_DECLARE_METATYPE(QItemSelection)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QAbstractProxyModel::QtScriptShell_QAbstractProxyModel(QObject*  parent)
    : QAbstractProxyModel(parent) {}

QtScriptShell_QAbstractProxyModel::~QtScriptShell_QAbstractProxyModel() {}

QModelIndex  QtScriptShell_QAbstractProxyModel::buddy(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("buddy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("buddy") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::buddy(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::canFetchMore(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("canFetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canFetchMore") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::canFetchMore(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QAbstractProxyModel::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QAbstractProxyModel::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QAbstractProxyModel::columnCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("columnCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("columnCount") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractProxyModel::columnCount() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QAbstractProxyModel::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QAbstractProxyModel::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QVariant  QtScriptShell_QAbstractProxyModel::data(const QModelIndex&  proxyIndex, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::data(proxyIndex, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, proxyIndex)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("dropMimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropMimeData") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::dropMimeData(data, action, row, column, parent);
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

bool  QtScriptShell_QAbstractProxyModel::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

void QtScriptShell_QAbstractProxyModel::fetchMore(const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("fetchMore");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fetchMore") & QScriptValue::QObjectMember)) {
        QAbstractProxyModel::fetchMore(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent));
    }
}

Qt::ItemFlags  QtScriptShell_QAbstractProxyModel::flags(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("flags");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("flags") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::flags(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<Qt::ItemFlags >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::hasChildren(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("hasChildren");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasChildren") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::hasChildren(parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QVariant  QtScriptShell_QAbstractProxyModel::headerData(int  section, Qt::Orientation  orientation, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("headerData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("headerData") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::headerData(section, orientation, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, section)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

QModelIndex  QtScriptShell_QAbstractProxyModel::index(int  row, int  column, const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("index");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("index") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractProxyModel::index() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::insertColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertColumns") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::insertColumns(column, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::insertRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("insertRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertRows") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::insertRows(row, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

QMap<int , QVariant >  QtScriptShell_QAbstractProxyModel::itemData(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("itemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemData") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::itemData(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QMap<int , QVariant > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

QModelIndex  QtScriptShell_QAbstractProxyModel::mapFromSource(const QModelIndex&  sourceIndex) const
{
    QScriptValue _q_function = __qtscript_self.property("mapFromSource");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mapFromSource") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractProxyModel::mapFromSource() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sourceIndex)));
    }
}

QItemSelection  QtScriptShell_QAbstractProxyModel::mapSelectionFromSource(const QItemSelection&  selection) const
{
    QScriptValue _q_function = __qtscript_self.property("mapSelectionFromSource");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mapSelectionFromSource") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::mapSelectionFromSource(selection);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QItemSelection >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selection)));
    }
}

QItemSelection  QtScriptShell_QAbstractProxyModel::mapSelectionToSource(const QItemSelection&  selection) const
{
    QScriptValue _q_function = __qtscript_self.property("mapSelectionToSource");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mapSelectionToSource") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::mapSelectionToSource(selection);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QItemSelection >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selection)));
    }
}

QModelIndex  QtScriptShell_QAbstractProxyModel::mapToSource(const QModelIndex&  proxyIndex) const
{
    QScriptValue _q_function = __qtscript_self.property("mapToSource");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mapToSource") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractProxyModel::mapToSource() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, proxyIndex)));
    }
}

QList<QModelIndex >  QtScriptShell_QAbstractProxyModel::match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const
{
    QScriptValue _q_function = __qtscript_self.property("match");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("match") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::match(start, role, value, hits, flags);
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

QMimeData*  QtScriptShell_QAbstractProxyModel::mimeData(const QList<QModelIndex >&  indexes) const
{
    QScriptValue _q_function = __qtscript_self.property("mimeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeData") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::mimeData(indexes);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QMimeData* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, indexes)));
    }
}

QStringList  QtScriptShell_QAbstractProxyModel::mimeTypes() const
{
    QScriptValue _q_function = __qtscript_self.property("mimeTypes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mimeTypes") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::mimeTypes();
    } else {
        return qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self));
    }
}

QModelIndex  QtScriptShell_QAbstractProxyModel::parent(const QModelIndex&  child) const
{
    QScriptValue _q_function = __qtscript_self.property("parent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parent") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractProxyModel::parent() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::removeColumns(int  column, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeColumns");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeColumns") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::removeColumns(column, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::removeRows(int  row, int  count, const QModelIndex&  parent)
{
    QScriptValue _q_function = __qtscript_self.property("removeRows");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("removeRows") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::removeRows(row, count, parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)
            << qScriptValueFromValue(_q_engine, count)
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

void QtScriptShell_QAbstractProxyModel::revert()
{
    QScriptValue _q_function = __qtscript_self.property("revert");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("revert") & QScriptValue::QObjectMember)) {
        QAbstractProxyModel::revert();
    } else {
        _q_function.call(__qtscript_self);
    }
}

int  QtScriptShell_QAbstractProxyModel::rowCount(const QModelIndex&  parent) const
{
    QScriptValue _q_function = __qtscript_self.property("rowCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowCount") & QScriptValue::QObjectMember)) {
        qFatal("QAbstractProxyModel::rowCount() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::setData(const QModelIndex&  index, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::setData(index, value, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role)
{
    QScriptValue _q_function = __qtscript_self.property("setHeaderData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setHeaderData") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::setHeaderData(section, orientation, value, role);
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

bool  QtScriptShell_QAbstractProxyModel::setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("setItemData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setItemData") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::setItemData(index, roles);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, roles)));
    }
}

void QtScriptShell_QAbstractProxyModel::setSourceModel(QAbstractItemModel*  sourceModel)
{
    QScriptValue _q_function = __qtscript_self.property("setSourceModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSourceModel") & QScriptValue::QObjectMember)) {
        QAbstractProxyModel::setSourceModel(sourceModel);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, sourceModel));
    }
}

void QtScriptShell_QAbstractProxyModel::sort(int  column, Qt::SortOrder  order)
{
    QScriptValue _q_function = __qtscript_self.property("sort");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sort") & QScriptValue::QObjectMember)) {
        QAbstractProxyModel::sort(column, order);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, order));
    }
}

QSize  QtScriptShell_QAbstractProxyModel::span(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("span");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("span") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::span(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QAbstractProxyModel::submit()
{
    QScriptValue _q_function = __qtscript_self.property("submit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("submit") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::submit();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

Qt::DropActions  QtScriptShell_QAbstractProxyModel::supportedDropActions() const
{
    QScriptValue _q_function = __qtscript_self.property("supportedDropActions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportedDropActions") & QScriptValue::QObjectMember)) {
        return QAbstractProxyModel::supportedDropActions();
    } else {
        return qscriptvalue_cast<Qt::DropActions >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QAbstractProxyModel::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QAbstractProxyModel::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

