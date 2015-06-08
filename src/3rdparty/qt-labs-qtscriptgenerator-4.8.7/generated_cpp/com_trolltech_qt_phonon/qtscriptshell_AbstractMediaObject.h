#ifndef QTSCRIPTSHELL_ABSTRACTMEDIAOBJECT_H
#define QTSCRIPTSHELL_ABSTRACTMEDIAOBJECT_H

#include <mediaobjectinterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractMediaObject : public Phonon::MediaObjectInterface
{
public:
    QtScriptShell_AbstractMediaObject();
    ~QtScriptShell_AbstractMediaObject();

    qint64  currentTime() const;
    QString  errorString() const;
    Phonon::ErrorType  errorType() const;
    bool  hasVideo() const;
    bool  isSeekable() const;
    void pause();
    void play();
    int  prefinishMark() const;
    qint64  remainingTime() const;
    void seek(qint64  milliseconds);
    void setNextSource(const Phonon::MediaSource&  source);
    void setPrefinishMark(int  arg__1);
    void setSource(const Phonon::MediaSource&  arg__1);
    void setTickInterval(int  interval);
    void setTransitionTime(int  arg__1);
    Phonon::MediaSource  source() const;
    Phonon::State  state() const;
    void stop();
    int  tickInterval() const;
    qint64  totalTime() const;
    int  transitionTime() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTMEDIAOBJECT_H
