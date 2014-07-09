#include "qtscriptshell_QAccessibleWidget.h"

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
Q_DECLARE_METATYPE(QAccessible::RelationFlag)
Q_DECLARE_METATYPE(QAccessibleInterface**)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QFlags<QAccessible::StateFlag>)

QtScriptShell_QAccessibleWidget::QtScriptShell_QAccessibleWidget(QWidget*  o, QAccessible::Role  r, const QString&  name)
    : QAccessibleWidget(o, r, name) {}

QtScriptShell_QAccessibleWidget::~QtScriptShell_QAccessibleWidget() {}

QString  QtScriptShell_QAccessibleWidget::actionText(int  action, QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("actionText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionText") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::actionText(action, t, child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleWidget::childAt(int  x, int  y) const
{
    QScriptValue _q_function = __qtscript_self.property("childAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childAt") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::childAt(x, y);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, x)
            << qScriptValueFromValue(_q_engine, y)));
    }
}

int  QtScriptShell_QAccessibleWidget::childCount() const
{
    QScriptValue _q_function = __qtscript_self.property("childCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childCount") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::childCount();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QAccessibleWidget::doAction(int  action, int  child, const QList<QVariant >&  params)
{
    QScriptValue _q_function = __qtscript_self.property("doAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doAction") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::doAction(action, child, params);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, params)));
    }
}

int  QtScriptShell_QAccessibleWidget::indexOfChild(const QAccessibleInterface*  child) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOfChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOfChild") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::indexOfChild(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(child))));
    }
}

bool  QtScriptShell_QAccessibleWidget::isValid() const
{
    QScriptValue _q_function = __qtscript_self.property("isValid");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isValid") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::isValid();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QAccessibleWidget::navigate(QAccessible::RelationFlag  rel, int  entry, QAccessibleInterface**  target) const
{
    QScriptValue _q_function = __qtscript_self.property("navigate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("navigate") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::navigate(rel, entry, target);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rel)
            << qScriptValueFromValue(_q_engine, entry)
            << qScriptValueFromValue(_q_engine, target)));
    }
}

QObject*  QtScriptShell_QAccessibleWidget::object() const
{
    QScriptValue _q_function = __qtscript_self.property("object");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("object") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::object();
    } else {
        return qscriptvalue_cast<QObject* >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QAccessibleWidget::rect(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("rect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rect") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::rect(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QAccessible::Relation  QtScriptShell_QAccessibleWidget::relationTo(int  child, const QAccessibleInterface*  other, int  otherChild) const
{
    QScriptValue _q_function = __qtscript_self.property("relationTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("relationTo") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::relationTo(child, other, otherChild);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Relation >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, const_cast<QAccessibleInterface *>(other))
            << qScriptValueFromValue(_q_engine, otherChild)));
    }
}

QAccessible::Role  QtScriptShell_QAccessibleWidget::role(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("role");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("role") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::role(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::Role >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

void QtScriptShell_QAccessibleWidget::setText(QAccessible::Text  t, int  child, const QString&  text)
{
    QScriptValue _q_function = __qtscript_self.property("setText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setText") & QScriptValue::QObjectMember)) {
        QAccessibleWidget::setText(t, child, text);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)
            << qScriptValueFromValue(_q_engine, text));
    }
}

QAccessible::State  QtScriptShell_QAccessibleWidget::state(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("state");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("state") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::state(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAccessible::State >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

QString  QtScriptShell_QAccessibleWidget::text(QAccessible::Text  t, int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("text");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("text") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::text(t, child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, t)
            << qScriptValueFromValue(_q_engine, child)));
    }
}

int  QtScriptShell_QAccessibleWidget::userActionCount(int  child) const
{
    QScriptValue _q_function = __qtscript_self.property("userActionCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("userActionCount") & QScriptValue::QObjectMember)) {
        return QAccessibleWidget::userActionCount(child);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, child)));
    }
}

