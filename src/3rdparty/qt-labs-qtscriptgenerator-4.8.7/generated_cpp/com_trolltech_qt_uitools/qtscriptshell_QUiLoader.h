#ifndef QTSCRIPTSHELL_QUILOADER_H
#define QTSCRIPTSHELL_QUILOADER_H

#include <quiloader.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QUiLoader : public QUiLoader
{
public:
    QtScriptShell_QUiLoader(QObject*  parent = 0);
    ~QtScriptShell_QUiLoader();

    void childEvent(QChildEvent*  arg__1);
    QAction*  createAction(QObject*  parent = 0, const QString&  name = QString());
    QActionGroup*  createActionGroup(QObject*  parent = 0, const QString&  name = QString());
    QLayout*  createLayout(const QString&  className, QObject*  parent = 0, const QString&  name = QString());
    QWidget*  createWidget(const QString&  className, QWidget*  parent = 0, const QString&  name = QString());
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUILOADER_H
