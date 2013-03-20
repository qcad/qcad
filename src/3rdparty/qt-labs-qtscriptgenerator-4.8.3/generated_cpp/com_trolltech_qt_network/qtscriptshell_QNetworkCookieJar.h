#ifndef QTSCRIPTSHELL_QNETWORKCOOKIEJAR_H
#define QTSCRIPTSHELL_QNETWORKCOOKIEJAR_H

#include <qnetworkcookiejar.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QNetworkCookieJar : public QNetworkCookieJar
{
public:
    QtScriptShell_QNetworkCookieJar(QObject*  parent = 0);
    ~QtScriptShell_QNetworkCookieJar();

    void childEvent(QChildEvent*  arg__1);
    QList<QNetworkCookie >  cookiesForUrl(const QUrl&  url) const;
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  setCookiesFromUrl(const QList<QNetworkCookie >&  cookieList, const QUrl&  url);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKCOOKIEJAR_H
