#ifndef QTSCRIPTSHELL_QWEBPAGE_H
#define QTSCRIPTSHELL_QWEBPAGE_H

#include <qwebpage.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QWebPage : public QWebPage
{
public:
    QtScriptShell_QWebPage(QObject*  parent = 0);
    ~QtScriptShell_QWebPage();

    bool  acceptNavigationRequest(QWebFrame*  frame, const QNetworkRequest&  request, QWebPage::NavigationType  type);
    void childEvent(QChildEvent*  arg__1);
    QString  chooseFile(QWebFrame*  originatingFrame, const QString&  oldFile);
    QObject*  createPlugin(const QString&  classid, const QUrl&  url, const QStringList&  paramNames, const QStringList&  paramValues);
    QWebPage*  createWindow(QWebPage::WebWindowType  type);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  extension(QWebPage::Extension  extension, const QWebPage::ExtensionOption*  option = 0, QWebPage::ExtensionReturn*  output = 0);
    void javaScriptAlert(QWebFrame*  originatingFrame, const QString&  msg);
    bool  javaScriptConfirm(QWebFrame*  originatingFrame, const QString&  msg);
    void javaScriptConsoleMessage(const QString&  message, int  lineNumber, const QString&  sourceID);
    bool  javaScriptPrompt(QWebFrame*  originatingFrame, const QString&  msg, const QString&  defaultValue, QString*  result);
    bool  supportsExtension(QWebPage::Extension  extension) const;
    void timerEvent(QTimerEvent*  arg__1);
    void triggerAction(QWebPage::WebAction  action, bool  checked = false);
    QString  userAgentForUrl(const QUrl&  url) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBPAGE_H
