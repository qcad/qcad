#ifndef QTSCRIPTSHELL_ABSTRACTVOLUMEFADER_H
#define QTSCRIPTSHELL_ABSTRACTVOLUMEFADER_H

#include <volumefaderinterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractVolumeFader : public Phonon::VolumeFaderInterface
{
public:
    QtScriptShell_AbstractVolumeFader();
    ~QtScriptShell_AbstractVolumeFader();

    Phonon::VolumeFaderEffect::FadeCurve  fadeCurve() const;
    void fadeTo(float  arg__1, int  arg__2);
    void setFadeCurve(Phonon::VolumeFaderEffect::FadeCurve  arg__1);
    void setVolume(float  arg__1);
    float  volume() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTVOLUMEFADER_H
