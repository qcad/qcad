#include "qtscriptshell_QTreeWidgetItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
#include <qfont.h>
#include <qicon.h>
#include <qlist.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qtreewidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QTreeWidgetItem*)

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, QTreeWidgetItem*  after, int  type)
    : QTreeWidgetItem(view, after, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, const QStringList&  strings, int  type)
    : QTreeWidgetItem(view, strings, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, int  type)
    : QTreeWidgetItem(view, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, QTreeWidgetItem*  after, int  type)
    : QTreeWidgetItem(parent, after, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, const QStringList&  strings, int  type)
    : QTreeWidgetItem(parent, strings, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, int  type)
    : QTreeWidgetItem(parent, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(const QStringList&  strings, int  type)
    : QTreeWidgetItem(strings, type) {}

QtScriptShell_QTreeWidgetItem::QtScriptShell_QTreeWidgetItem(int  type)
    : QTreeWidgetItem(type) {}

QtScriptShell_QTreeWidgetItem::~QtScriptShell_QTreeWidgetItem() {}

QTreeWidgetItem*  QtScriptShell_QTreeWidgetItem::clone() const
{
    QScriptValue _q_function = __qtscript_self.property("clone");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clone") & QScriptValue::QObjectMember)) {
        return QTreeWidgetItem::clone();
    } else {
        return qscriptvalue_cast<QTreeWidgetItem* >(_q_function.call(__qtscript_self));
    }
}

QVariant  QtScriptShell_QTreeWidgetItem::data(int  column, int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        return QTreeWidgetItem::data(column, role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, role)));
    }
}

void QtScriptShell_QTreeWidgetItem::setData(int  column, int  role, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)) {
        QTreeWidgetItem::setData(column, role, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)
            << qScriptValueFromValue(_q_engine, role)
            << qScriptValueFromValue(_q_engine, value));
    }
}

