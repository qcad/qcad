#include "qtscriptshell_QAccessibleInterface.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAccessible::Text)
Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(QAccessible::RelationFlag)
Q_DECLARE_METATYPE(QAccessibleInterface**)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QFlags<QAccessible::StateFlag>)

QtScriptShell_QAccessibleInterface::QtScriptShell_QAccessibleInterface()
    : QAccessibleInterface() {}

QtScriptShell_QAccessibleInterface::~QtScriptShell_QAccessibleInterface() {}

QString  QtScriptShell_QAccessibleInterface::actionText(int  action, QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("actionText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionText") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::actionText() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleInterface::childAt(int  x, int  y) const
{
    QScriptValue _q_function = __qtscript_self.property("childAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childAt") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::childAt() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, x)
            << qScriptValueFromValue(_q_engine, y)));
    }
}

int  QtScriptShell_QAccessibleInterface::childCount() const
{
    QScriptValue _q_function = __qtscript_self.property("childCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::childCount() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QAccessibleInterface::doAction(int  action, int  child, const QList<QVariant >&  params)
{
    QScriptValue _q_function = __qtscript_self.property("doAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doAction") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::doAction() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, params)));
    }
}

int  QtScriptShell_QAccessibleInterface::indexOfChild(const QAccessibleInterface*  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOfChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOfChild") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::indexOfChild() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(arg__1))));
    }
}

bool  QtScriptShell_QAccessibleInterface::isValid() const
{
    QScriptValue _q_function = __qtscript_self.property("isValid");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isValid") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::isValid() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleInterface::navigate(QAccessible::RelationFlag  relation, int  index, QAccessibleInterface**  iface) const
{
    QScriptValue _q_function = __qtscript_self.property("navigate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("navigate") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::navigate() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, relation)
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, iface)));
    }
}

QObject*  QtScriptShell_QAccessibleInterface::object() const
{
    QScriptValue _q_function = __qtscript_self.property("object");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("object") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::object() is abstract!");
    } else {
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QAccessibleInterface::rect(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("rect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rect") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::rect() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QAccessible::Relation  QtScriptShell_QAccessibleInterface::relationTo(int  child, const QAccessibleInterface*  other, int  otherChild) const
{
    QScriptValue _q_function = __qtscript_self.property("relationTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relationTo") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::relationTo() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Relation >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(other))
            << qScriptValueFromValue(_q_engine, otherChild)));
    }
}

QAccessible::Role  QtScriptShell_QAccessibleInterface::role(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("role");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("role") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::role() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Role >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

void QtScriptShell_QAccessibleInterface::setText(QAccessible::Text  t, int  child, const QString&  text)
{
    QScriptValue _q_function = __qtscript_self.property("setText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setText") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::setText() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, text));
    }
}

QAccessible::State  QtScriptShell_QAccessibleInterface::state(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("state");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("state") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::state() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::State >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QString  QtScriptShell_QAccessibleInterface::text(QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("text");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("text") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::text() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleInterface::userActionCount(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("userActionCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("userActionCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleInterface::userActionCount() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

