#include "qtscriptshell_QListWidgetItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
#include <qdatastream.h>
#include <qfont.h>
#include <qicon.h>
#include <qlistwidget.h>
#include <qsize.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QListWidgetItem*)

QtScriptShell_QListWidgetItem::QtScriptShell_QListWidgetItem(QListWidget*  view, int  type)
    : QListWidgetItem(view, type) {}

QtScriptShell_QListWidgetItem::QtScriptShell_QListWidgetItem(const QIcon&  icon, const QString&  text, QListWidget*  view, int  type)
    : QListWidgetItem(icon, text, view, type) {}

QtScriptShell_QListWidgetItem::QtScriptShell_QListWidgetItem(const QString&  text, QListWidget*  view, int  type)
    : QListWidgetItem(text, view, type) {}

QtScriptShell_QListWidgetItem::~QtScriptShell_QListWidgetItem() {}

QListWidgetItem*  QtScriptShell_QListWidgetItem::clone() const
{
    QScriptValue _q_function = __qtscript_self.property("clone");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("clone") & QScriptValue::QObjectMember)) {
        return QListWidgetItem::clone();
    } else {
        return qscriptvalue_cast<QListWidgetItem* >(_q_function.call(__qtscript_self));
    }
}

QVariant  QtScriptShell_QListWidgetItem::data(int  role) const
{
    QScriptValue _q_function = __qtscript_self.property("data");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("data") & QScriptValue::QObjectMember)) {
        return QListWidgetItem::data(role);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, role)));
    }
}

void QtScriptShell_QListWidgetItem::setData(int  role, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setData") & QScriptValue::QObjectMember)) {
        QListWidgetItem::setData(role, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, role)
            << qScriptValueFromValue(_q_engine, value));
    }
}

