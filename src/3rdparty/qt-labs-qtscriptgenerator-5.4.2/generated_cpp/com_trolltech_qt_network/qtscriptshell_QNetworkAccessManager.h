#ifndef QTSCRIPTSHELL_QNETWORKACCESSMANAGER_H
#define QTSCRIPTSHELL_QNETWORKACCESSMANAGER_H

#include <qnetworkaccessmanager.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QNetworkAccessManager : public QNetworkAccessManager
{
public:
    QtScriptShell_QNetworkAccessManager(QObject*  parent = 0);
    ~QtScriptShell_QNetworkAccessManager();

    void childEvent(QChildEvent*  arg__1);
    QNetworkReply*  createRequest(QNetworkAccessManager::Operation  op, const QNetworkRequest&  request, QIODevice*  outgoingData = 0);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKACCESSMANAGER_H
