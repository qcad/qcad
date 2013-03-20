#ifndef QTSCRIPTSHELL_QMOVIE_H
#define QTSCRIPTSHELL_QMOVIE_H

#include <qmovie.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QMovie : public QMovie
{
public:
    QtScriptShell_QMovie(QIODevice*  device, const QByteArray&  format = QByteArray(), QObject*  parent = 0);
    QtScriptShell_QMovie(QObject*  parent = 0);
    QtScriptShell_QMovie(const QString&  fileName, const QByteArray&  format = QByteArray(), QObject*  parent = 0);
    ~QtScriptShell_QMovie();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMOVIE_H
