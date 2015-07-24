#ifndef QTSCRIPTSHELL_QFTP_H
#define QTSCRIPTSHELL_QFTP_H

#include <qftp.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFtp : public QFtp
{
public:
    QtScriptShell_QFtp(QObject*  parent = 0);
    ~QtScriptShell_QFtp();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFTP_H
