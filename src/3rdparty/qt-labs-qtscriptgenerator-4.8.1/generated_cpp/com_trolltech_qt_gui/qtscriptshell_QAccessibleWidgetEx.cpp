#include "qtscriptshell_QAccessibleWidgetEx.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>
#include <qaccessiblewidget.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAccessible::Text)
Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(QAccessible::Method)
Q_DECLARE_METATYPE(QAccessible::RelationFlag)
Q_DECLARE_METATYPE(QAccessibleInterface**)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QFlags<QAccessible::StateFlag>)

QtScriptShell_QAccessibleWidgetEx::QtScriptShell_QAccessibleWidgetEx(QWidget*  o, QAccessible::Role  r, const QString&  name)
    : QAccessibleWidgetEx(o, r, name) {}

QtScriptShell_QAccessibleWidgetEx::~QtScriptShell_QAccessibleWidgetEx() {}

QString  QtScriptShell_QAccessibleWidgetEx::actionText(int  action, QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("actionText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionText") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::actionText(action, t, child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleWidgetEx::childAt(int  x, int  y) const
{
    QScriptValue _q_function = __qtscript_self.property("childAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childAt") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::childAt(x, y);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, x)
            << qScriptValueFromValue(_q_engine, y)));
    }
}

int  QtScriptShell_QAccessibleWidgetEx::childCount() const
{
    QScriptValue _q_function = __qtscript_self.property("childCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childCount") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::childCount();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QAccessibleWidgetEx::doAction(int  action, int  child, const QList<QVariant >&  params)
{
    QScriptValue _q_function = __qtscript_self.property("doAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doAction") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::doAction(action, child, params);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, params)));
    }
}

int  QtScriptShell_QAccessibleWidgetEx::indexOfChild(const QAccessibleInterface*  child) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOfChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOfChild") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::indexOfChild(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(child))));
    }
}

QVariant  QtScriptShell_QAccessibleWidgetEx::invokeMethodEx(QAccessible::Method  method, int  child, const QList<QVariant >&  params)
{
    QScriptValue _q_function = __qtscript_self.property("invokeMethodEx");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invokeMethodEx") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::invokeMethodEx(method, child, params);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, method)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, params)));
    }
}

bool  QtScriptShell_QAccessibleWidgetEx::isValid() const
{
    QScriptValue _q_function = __qtscript_self.property("isValid");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isValid") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::isValid();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleWidgetEx::navigate(QAccessible::RelationFlag  rel, int  entry, QAccessibleInterface**  target) const
{
    QScriptValue _q_function = __qtscript_self.property("navigate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("navigate") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::navigate(rel, entry, target);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rel)
            << qScriptValueFromValue(_q_engine, entry)
            << qScriptValueFromValue(_q_engine, target)));
    }
}

QObject*  QtScriptShell_QAccessibleWidgetEx::object() const
{
    QScriptValue _q_function = __qtscript_self.property("object");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("object") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::object();
    } else {
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QAccessibleWidgetEx::rect(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("rect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rect") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::rect(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QAccessible::Relation  QtScriptShell_QAccessibleWidgetEx::relationTo(int  child, const QAccessibleInterface*  other, int  otherChild) const
{
    QScriptValue _q_function = __qtscript_self.property("relationTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relationTo") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::relationTo(child, other, otherChild);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Relation >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(other))
            << qScriptValueFromValue(_q_engine, otherChild)));
    }
}

QAccessible::Role  QtScriptShell_QAccessibleWidgetEx::role(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("role");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("role") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::role(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Role >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

void QtScriptShell_QAccessibleWidgetEx::setText(QAccessible::Text  t, int  child, const QString&  text)
{
    QScriptValue _q_function = __qtscript_self.property("setText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setText") & QScriptValue::QObjectMember)) {
        QAccessibleWidgetEx::setText(t, child, text);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, text));
    }
}

QAccessible::State  QtScriptShell_QAccessibleWidgetEx::state(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("state");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("state") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::state(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::State >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QString  QtScriptShell_QAccessibleWidgetEx::text(QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("text");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("text") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::text(t, child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleWidgetEx::userActionCount(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("userActionCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("userActionCount") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::userActionCount(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QVariant  QtScriptShell_QAccessibleWidgetEx::virtual_hook(const QVariant&  data)
{
    QScriptValue _q_function = __qtscript_self.property("virtual_hook");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("virtual_hook") & QScriptValue::QObjectMember)) {
        return QAccessibleWidgetEx::virtual_hook(data);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)));
    }
}

