#ifndef QTSCRIPTSHELL_QABSTRACTMESSAGEHANDLER_H
#define QTSCRIPTSHELL_QABSTRACTMESSAGEHANDLER_H

#include <qabstractmessagehandler.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractMessageHandler : public QAbstractMessageHandler
{
public:
    QtScriptShell_QAbstractMessageHandler(QObject*  parent = 0);
    ~QtScriptShell_QAbstractMessageHandler();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void handleMessage(QtMsgType  type, const QString&  description, const QUrl&  identifier, const QSourceLocation&  sourceLocation);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTMESSAGEHANDLER_H
