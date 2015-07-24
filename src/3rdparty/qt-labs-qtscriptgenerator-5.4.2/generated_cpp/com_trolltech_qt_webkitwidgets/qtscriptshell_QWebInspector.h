#ifndef QTSCRIPTSHELL_QWEBINSPECTOR_H
#define QTSCRIPTSHELL_QWEBINSPECTOR_H

#include <qwebinspector.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWebInspector : public QWebInspector
{
public:
    QtScriptShell_QWebInspector(QWidget*  parent = 0);
    ~QtScriptShell_QWebInspector();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBINSPECTOR_H
