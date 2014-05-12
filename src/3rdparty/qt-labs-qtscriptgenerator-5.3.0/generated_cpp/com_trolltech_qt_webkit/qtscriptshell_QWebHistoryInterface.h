#ifndef QTSCRIPTSHELL_QWEBHISTORYINTERFACE_H
#define QTSCRIPTSHELL_QWEBHISTORYINTERFACE_H

#include <qwebhistoryinterface.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWebHistoryInterface : public QWebHistoryInterface
{
public:
    QtScriptShell_QWebHistoryInterface(QObject*  parent = 0);
    ~QtScriptShell_QWebHistoryInterface();

    void addHistoryEntry(const QString&  url);
    bool  historyContains(const QString&  url) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBHISTORYINTERFACE_H
