#ifndef QTSCRIPTSHELL_QINPUTCONTEXTFACTORY_H
#define QTSCRIPTSHELL_QINPUTCONTEXTFACTORY_H

#include <qinputcontextfactory.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QInputContextFactory : public QInputContextFactory
{
public:
    QtScriptShell_QInputContextFactory();
    ~QtScriptShell_QInputContextFactory();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QINPUTCONTEXTFACTORY_H
