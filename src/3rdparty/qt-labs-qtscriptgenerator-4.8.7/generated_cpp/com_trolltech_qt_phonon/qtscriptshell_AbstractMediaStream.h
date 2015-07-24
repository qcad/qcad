#ifndef QTSCRIPTSHELL_ABSTRACTMEDIASTREAM_H
#define QTSCRIPTSHELL_ABSTRACTMEDIASTREAM_H

#include <abstractmediastream.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractMediaStream : public Phonon::AbstractMediaStream
{
public:
    QtScriptShell_AbstractMediaStream(QObject*  parent = 0);
    ~QtScriptShell_AbstractMediaStream();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void enoughData();
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void needData();
    void reset();
    void seekStream(qint64  offset);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTMEDIASTREAM_H
