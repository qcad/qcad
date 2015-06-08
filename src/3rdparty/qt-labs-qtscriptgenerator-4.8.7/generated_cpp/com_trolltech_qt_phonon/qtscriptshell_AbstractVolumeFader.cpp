#include "qtscriptshell_AbstractVolumeFader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(Phonon::VolumeFaderEffect::FadeCurve)

QtScriptShell_AbstractVolumeFader::QtScriptShell_AbstractVolumeFader()
    : Phonon::VolumeFaderInterface() {}

QtScriptShell_AbstractVolumeFader::~QtScriptShell_AbstractVolumeFader() {}

Phonon::VolumeFaderEffect::FadeCurve  QtScriptShell_AbstractVolumeFader::fadeCurve() const
{
    QScriptValue _q_function = __qtscript_self.property("fadeCurve");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fadeCurve") & QScriptValue::QObjectMember)) {
        return Phonon::VolumeFaderInterface::fadeCurve();
    } else {
        return qscriptvalue_cast<Phonon::VolumeFaderEffect::FadeCurve >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_AbstractVolumeFader::fadeTo(float  arg__1, int  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("fadeTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fadeTo") & QScriptValue::QObjectMember)) {
        Phonon::VolumeFaderInterface::fadeTo(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2));
    }
}

void QtScriptShell_AbstractVolumeFader::setFadeCurve(Phonon::VolumeFaderEffect::FadeCurve  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setFadeCurve");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setFadeCurve") & QScriptValue::QObjectMember)) {
        Phonon::VolumeFaderInterface::setFadeCurve(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_AbstractVolumeFader::setVolume(float  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setVolume");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setVolume") & QScriptValue::QObjectMember)) {
        Phonon::VolumeFaderInterface::setVolume(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

float  QtScriptShell_AbstractVolumeFader::volume() const
{
    QScriptValue _q_function = __qtscript_self.property("volume");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("volume") & QScriptValue::QObjectMember)) {
        return Phonon::VolumeFaderInterface::volume();
    } else {
        return qscriptvalue_cast<float >(_q_function.call(__qtscript_self));
    }
}

