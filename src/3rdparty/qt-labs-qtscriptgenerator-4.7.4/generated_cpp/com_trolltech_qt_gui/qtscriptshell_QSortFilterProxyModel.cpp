#include "qtscriptshell_QSortFilterProxyModel.h"

#include <QtScript/QScriptEngine>
#include <QItemSelection>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qitemselectionmodel.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qregexp.h>
#include <qsize.h>
#include <qsortfilterproxymodel.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QModelIndex)

QtScriptShell_QSortFilterProxyModel::QtScriptShell_QSortFilterProxyModel(QObject*  parent)
    : QSortFilterProxyModel(parent) {}

QtScriptShell_QSortFilterProxyModel::~QtScriptShell_QSortFilterProxyModel() {}

bool  QtScriptShell_QSortFilterProxyModel::filterAcceptsColumn(int  source_column, const QModelIndex&  source_parent) const
{
    QScriptValue _q_function = __qtscript_self.property("filterAcceptsColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("filterAcceptsColumn") & QScriptValue::QObjectMember)) {
        return QSortFilterProxyModel::filterAcceptsColumn(source_column, source_parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, source_column)
            << qScriptValueFromValue(_q_engine, source_parent)));
    }
}

bool  QtScriptShell_QSortFilterProxyModel::filterAcceptsRow(int  source_row, const QModelIndex&  source_parent) const
{
    QScriptValue _q_function = __qtscript_self.property("filterAcceptsRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("filterAcceptsRow") & QScriptValue::QObjectMember)) {
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, source_row)
            << qScriptValueFromValue(_q_engine, source_parent)));
    }
}

bool  QtScriptShell_QSortFilterProxyModel::lessThan(const QModelIndex&  left, const QModelIndex&  right) const
{
    QScriptValue _q_function = __qtscript_self.property("lessThan");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("lessThan") & QScriptValue::QObjectMember)) {
        return QSortFilterProxyModel::lessThan(left, right);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, left)
            << qScriptValueFromValue(_q_engine, right)));
    }
}

