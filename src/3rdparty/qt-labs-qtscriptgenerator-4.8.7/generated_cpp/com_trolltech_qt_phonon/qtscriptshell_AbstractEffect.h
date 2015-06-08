#ifndef QTSCRIPTSHELL_ABSTRACTEFFECT_H
#define QTSCRIPTSHELL_ABSTRACTEFFECT_H

#include <effectinterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractEffect : public Phonon::EffectInterface
{
public:
    QtScriptShell_AbstractEffect();
    ~QtScriptShell_AbstractEffect();

    QVariant  parameterValue(const Phonon::EffectParameter&  arg__1) const;
    QList<Phonon::EffectParameter >  parameters() const;
    void setParameterValue(const Phonon::EffectParameter&  arg__1, const QVariant&  newValue);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTEFFECT_H
