#include "qtscriptshell_QAccessibleInterfaceEx.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAccessible::Text)
Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(QAccessible::Method)
Q_DECLARE_METATYPE(QAccessible::RelationFlag)
Q_DECLARE_METATYPE(QAccessibleInterface**)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QFlags<QAccessible::StateFlag>)

QtScriptShell_QAccessibleInterfaceEx::QtScriptShell_QAccessibleInterfaceEx()
    : QAccessibleInterfaceEx() {}

QtScriptShell_QAccessibleInterfaceEx::~QtScriptShell_QAccessibleInterfaceEx() {}

QString  QtScriptShell_QAccessibleInterfaceEx::actionText(int  action, QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("actionText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionText") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::actionText() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleInterfaceEx::childAt(int  x, int  y) const
{
    QScriptValue _q_function = __qtscript_self.property("childAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childAt") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::childAt() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, x)
            << qScriptValueFromValue(_q_engine, y)));
    }
}

int  QtScriptShell_QAccessibleInterfaceEx::childCount() const
{
    QScriptValue _q_function = __qtscript_self.property("childCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::childCount() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QAccessibleInterfaceEx::doAction(int  action, int  child, const QList<QVariant >&  params)
{
    QScriptValue _q_function = __qtscript_self.property("doAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doAction") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::doAction() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, params)));
    }
}

int  QtScriptShell_QAccessibleInterfaceEx::indexOfChild(const QAccessibleInterface*  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOfChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOfChild") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::indexOfChild() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(arg__1))));
    }
}

QVariant  QtScriptShell_QAccessibleInterfaceEx::invokeMethodEx(QAccessible::Method  method, int  child, const QList<QVariant >&  params)
{
    QScriptValue _q_function = __qtscript_self.property("invokeMethodEx");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invokeMethodEx") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::invokeMethodEx() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, method)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, params)));
    }
}

bool  QtScriptShell_QAccessibleInterfaceEx::isValid() const
{
    QScriptValue _q_function = __qtscript_self.property("isValid");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isValid") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::isValid() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleInterfaceEx::navigate(QAccessible::RelationFlag  relation, int  index, QAccessibleInterface**  iface) const
{
    QScriptValue _q_function = __qtscript_self.property("navigate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("navigate") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::navigate() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, relation)
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, iface)));
    }
}

QObject*  QtScriptShell_QAccessibleInterfaceEx::object() const
{
    QScriptValue _q_function = __qtscript_self.property("object");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("object") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::object() is abstract!");
    } else {
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QAccessibleInterfaceEx::rect(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("rect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rect") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::rect() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QAccessible::Relation  QtScriptShell_QAccessibleInterfaceEx::relationTo(int  child, const QAccessibleInterface*  other, int  otherChild) const
{
    QScriptValue _q_function = __qtscript_self.property("relationTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relationTo") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::relationTo() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Relation >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(other))
            << qScriptValueFromValue(_q_engine, otherChild)));
    }
}

QAccessible::Role  QtScriptShell_QAccessibleInterfaceEx::role(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("role");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("role") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::role() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Role >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

void QtScriptShell_QAccessibleInterfaceEx::setText(QAccessible::Text  t, int  child, const QString&  text)
{
    QScriptValue _q_function = __qtscript_self.property("setText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setText") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::setText() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, text));
    }
}

QAccessible::State  QtScriptShell_QAccessibleInterfaceEx::state(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("state");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("state") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::state() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::State >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QString  QtScriptShell_QAccessibleInterfaceEx::text(QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("text");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("text") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::text() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleInterfaceEx::userActionCount(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("userActionCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("userActionCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterfaceEx::userActionCount() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QVariant  QtScriptShell_QAccessibleInterfaceEx::virtual_hook(const QVariant&  data)
{
    QScriptValue _q_function = __qtscript_self.property("virtual_hook");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("virtual_hook") & QScriptValue::QObjectMember)) {
        return QAccessibleInterfaceEx::virtual_hook(data);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)));
    }
}

