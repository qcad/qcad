#ifndef QTSCRIPTSHELL_QWEBPLUGINFACTORY_PLUGIN_H
#define QTSCRIPTSHELL_QWEBPLUGINFACTORY_PLUGIN_H

#include <qwebpluginfactory.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWebPluginFactory_Plugin : public QWebPluginFactory::Plugin
{
public:
    QtScriptShell_QWebPluginFactory_Plugin();
    ~QtScriptShell_QWebPluginFactory_Plugin();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBPLUGINFACTORY_PLUGIN_H
