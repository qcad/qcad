#ifndef QTSCRIPTSHELL_QCOREAPPLICATION_H
#define QTSCRIPTSHELL_QCOREAPPLICATION_H

#include <qcoreapplication.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QCoreApplication : public QCoreApplication
{
public:
    QtScriptShell_QCoreApplication(int&  argc, char**  argv, int  arg__3 = ApplicationFlags);
    ~QtScriptShell_QCoreApplication();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  notify(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCOREAPPLICATION_H
