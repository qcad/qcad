#include "qtscriptshell_AbstractAddon.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Phonon::AddonInterface::Interface)

QtScriptShell_AbstractAddon::QtScriptShell_AbstractAddon()
    : Phonon::AddonInterface() {}

QtScriptShell_AbstractAddon::~QtScriptShell_AbstractAddon() {}

bool  QtScriptShell_AbstractAddon::hasInterface(Phonon::AddonInterface::Interface  iface) const
{
    QScriptValue _q_function = __qtscript_self.property("hasInterface");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasInterface") & QScriptValue::QObjectMember)) {
        qFatal("AbstractAddon::hasInterface() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, iface)));
    }
}

QVariant  QtScriptShell_AbstractAddon::interfaceCall(Phonon::AddonInterface::Interface  iface, int  command, const QList<QVariant >&  arguments)
{
    QScriptValue _q_function = __qtscript_self.property("interfaceCall");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("interfaceCall") & QScriptValue::QObjectMember)) {
        qFatal("AbstractAddon::interfaceCall() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, iface)
            << qScriptValueFromValue(_q_engine, command)
            << qScriptValueFromValue(_q_engine, arguments)));
    }
}

