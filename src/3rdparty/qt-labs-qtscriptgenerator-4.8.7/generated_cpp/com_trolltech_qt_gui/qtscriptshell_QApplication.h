#ifndef QTSCRIPTSHELL_QAPPLICATION_H
#define QTSCRIPTSHELL_QAPPLICATION_H

#include <qapplication.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QApplication : public QApplication
{
public:
    QtScriptShell_QApplication(int&  argc, char**  argv, QApplication::Type  arg__3, int  arg__4 = ApplicationFlags);
    QtScriptShell_QApplication(int&  argc, char**  argv, bool  GUIenabled, int  arg__4 = ApplicationFlags);
    QtScriptShell_QApplication(int&  argc, char**  argv, int  arg__3 = ApplicationFlags);
    ~QtScriptShell_QApplication();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  notify(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QAPPLICATION_H
