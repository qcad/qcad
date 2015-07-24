#include "qtscriptshell_AbstractEffect.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <effectparameter.h>
#include <qlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Phonon::EffectParameter)
Q_DECLARE_METATYPE(QList<Phonon::EffectParameter>)

QtScriptShell_AbstractEffect::QtScriptShell_AbstractEffect()
    : Phonon::EffectInterface() {}

QtScriptShell_AbstractEffect::~QtScriptShell_AbstractEffect() {}

QVariant  QtScriptShell_AbstractEffect::parameterValue(const Phonon::EffectParameter&  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("parameterValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parameterValue") & QScriptValue::QObjectMember)) {
        qFatal("AbstractEffect::parameterValue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QList<Phonon::EffectParameter >  QtScriptShell_AbstractEffect::parameters() const
{
    QScriptValue _q_function = __qtscript_self.property("parameters");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("parameters") & QScriptValue::QObjectMember)) {
        qFatal("AbstractEffect::parameters() is abstract!");
    } else {
        return qscriptvalue_cast<QList<Phonon::EffectParameter > >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_AbstractEffect::setParameterValue(const Phonon::EffectParameter&  arg__1, const QVariant&  newValue)
{
    QScriptValue _q_function = __qtscript_self.property("setParameterValue");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setParameterValue") & QScriptValue::QObjectMember)) {
        qFatal("AbstractEffect::setParameterValue() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, newValue));
    }
}

