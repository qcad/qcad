#ifndef QTSCRIPTSHELL_QWEBPLUGINFACTORY_EXTENSIONRETURN_H
#define QTSCRIPTSHELL_QWEBPLUGINFACTORY_EXTENSIONRETURN_H

#include <qwebpluginfactory.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QWebPluginFactory_ExtensionReturn : public QWebPluginFactory::ExtensionReturn
{
public:
    QtScriptShell_QWebPluginFactory_ExtensionReturn();
    ~QtScriptShell_QWebPluginFactory_ExtensionReturn();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBPLUGINFACTORY_EXTENSIONRETURN_H
