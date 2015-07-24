#ifndef QTSCRIPTSHELL_QWEBPAGE_ERRORPAGEEXTENSIONRETURN_H
#define QTSCRIPTSHELL_QWEBPAGE_ERRORPAGEEXTENSIONRETURN_H

#include <qwebpage.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QWebPage_ErrorPageExtensionReturn : public QWebPage::ErrorPageExtensionReturn
{
public:
    QtScriptShell_QWebPage_ErrorPageExtensionReturn();
    ~QtScriptShell_QWebPage_ErrorPageExtensionReturn();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBPAGE_ERRORPAGEEXTENSIONRETURN_H
