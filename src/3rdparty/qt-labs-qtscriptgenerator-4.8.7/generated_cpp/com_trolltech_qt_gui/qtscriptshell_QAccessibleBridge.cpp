#include "qtscriptshell_QAccessibleBridge.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QAccessibleInterface*)

QtScriptShell_QAccessibleBridge::QtScriptShell_QAccessibleBridge()
    : QAccessibleBridge() {}

QtScriptShell_QAccessibleBridge::~QtScriptShell_QAccessibleBridge() {}

void QtScriptShell_QAccessibleBridge::notifyAccessibilityUpdate(int  arg__1, QAccessibleInterface*  arg__2, int  arg__3)
{
    QScriptValue _q_function = __qtscript_self.property("notifyAccessibilityUpdate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("notifyAccessibilityUpdate") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleBridge::notifyAccessibilityUpdate() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)
            << qScriptValueFromValue(_q_engine, arg__3));
    }
}

void QtScriptShell_QAccessibleBridge::setRootObject(QAccessibleInterface*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setRootObject");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRootObject") & QScriptValue::QObjectMember)) {
        qFatal("QAccessibleBridge::setRootObject() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

