#ifndef QTSCRIPTSHELL_QWEBHISTORYINTERFACE_H
#define QTSCRIPTSHELL_QWEBHISTORYINTERFACE_H

#include <qwebhistoryinterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QWebHistoryInterface : public QWebHistoryInterface
{
public:
    QtScriptShell_QWebHistoryInterface(QObject*  parent = 0);
    ~QtScriptShell_QWebHistoryInterface();

    void addHistoryEntry(const QString&  url);
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  historyContains(const QString&  url) const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBHISTORYINTERFACE_H
