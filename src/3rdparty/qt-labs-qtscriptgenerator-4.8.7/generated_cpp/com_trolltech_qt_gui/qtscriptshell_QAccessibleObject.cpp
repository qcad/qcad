#include "qtscriptshell_QAccessibleObject.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>
#include <qaccessibleobject.h>
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

QtScriptShell_QAccessibleObject::QtScriptShell_QAccessibleObject(QObject*  object)
    : QAccessibleObject(object) {}

QtScriptShell_QAccessibleObject::~QtScriptShell_QAccessibleObject() {}

QString  QtScriptShell_QAccessibleObject::actionText(int  action, QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("actionText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionText") & QScriptValue::QObjectMember)) {
        return QAccessibleObject::actionText(action, t, child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleObject::childAt(int  x, int  y) const
{
    QScriptValue _q_function = __qtscript_self.property("childAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childAt") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::childAt() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, x)
            << qScriptValueFromValue(_q_engine, y)));
    }
}

int  QtScriptShell_QAccessibleObject::childCount() const
{
    QScriptValue _q_function = __qtscript_self.property("childCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childCount") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::childCount() is abstract!");
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QAccessibleObject::doAction(int  action, int  child, const QList<QVariant >&  params)
{
    QScriptValue _q_function = __qtscript_self.property("doAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doAction") & QScriptValue::QObjectMember)) {
        return QAccessibleObject::doAction(action, child, params);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, params)));
    }
}

int  QtScriptShell_QAccessibleObject::indexOfChild(const QAccessibleInterface*  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOfChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOfChild") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::indexOfChild() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(arg__1))));
    }
}

bool  QtScriptShell_QAccessibleObject::isValid() const
{
    QScriptValue _q_function = __qtscript_self.property("isValid");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isValid") & QScriptValue::QObjectMember)) {
        return QAccessibleObject::isValid();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleObject::navigate(QAccessible::RelationFlag  relation, int  index, QAccessibleInterface**  iface) const
{
    QScriptValue _q_function = __qtscript_self.property("navigate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("navigate") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::navigate() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, relation)
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, iface)));
    }
}

QObject*  QtScriptShell_QAccessibleObject::object() const
{
    QScriptValue _q_function = __qtscript_self.property("object");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("object") & QScriptValue::QObjectMember)) {
        return QAccessibleObject::object();
    } else {
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QAccessibleObject::rect(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("rect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rect") & QScriptValue::QObjectMember)) {
        return QAccessibleObject::rect(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QAccessible::Relation  QtScriptShell_QAccessibleObject::relationTo(int  child, const QAccessibleInterface*  other, int  otherChild) const
{
    QScriptValue _q_function = __qtscript_self.property("relationTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relationTo") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::relationTo() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Relation >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(other))
            << qScriptValueFromValue(_q_engine, otherChild)));
    }
}

QAccessible::Role  QtScriptShell_QAccessibleObject::role(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("role");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("role") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::role() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Role >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

void QtScriptShell_QAccessibleObject::setText(QAccessible::Text  t, int  child, const QString&  text)
{
    QScriptValue _q_function = __qtscript_self.property("setText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setText") & QScriptValue::QObjectMember)) {
        QAccessibleObject::setText(t, child, text);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, text));
    }
}

QAccessible::State  QtScriptShell_QAccessibleObject::state(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("state");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("state") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::state() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::State >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QString  QtScriptShell_QAccessibleObject::text(QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("text");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("text") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleObject::text() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleObject::userActionCount(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("userActionCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("userActionCount") & QScriptValue::QObjectMember)) {
        return QAccessibleObject::userActionCount(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

