#ifndef QTSCRIPTSHELL_QWEBPAGE_EXTENSIONRETURN_H
#define QTSCRIPTSHELL_QWEBPAGE_EXTENSIONRETURN_H

#include <qwebpage.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWebPage_ExtensionReturn : public QWebPage::ExtensionReturn
{
public:
    QtScriptShell_QWebPage_ExtensionReturn();
    ~QtScriptShell_QWebPage_ExtensionReturn();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBPAGE_EXTENSIONRETURN_H
