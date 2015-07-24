#ifndef QTSCRIPTSHELL_QGUIAPPLICATION_H
#define QTSCRIPTSHELL_QGUIAPPLICATION_H

#include <qguiapplication.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGuiApplication : public QGuiApplication
{
public:
    QtScriptShell_QGuiApplication(int&  argc, char**  argv, int  arg__3 = ApplicationFlags);
    ~QtScriptShell_QGuiApplication();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  notify(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGUIAPPLICATION_H
