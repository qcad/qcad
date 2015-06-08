#ifndef QTSCRIPTSHELL_QDESKTOPSERVICES_H
#define QTSCRIPTSHELL_QDESKTOPSERVICES_H

#include <qdesktopservices.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QDesktopServices : public QDesktopServices
{
public:
    QtScriptShell_QDesktopServices();
    ~QtScriptShell_QDesktopServices();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDESKTOPSERVICES_H
