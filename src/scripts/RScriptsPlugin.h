#ifndef RSCRIPTSPLUGIN_H_
#define RSCRIPTSPLUGIN_H_

#include <QDebug>
#include <QObject>
#include <QScriptEngine>
#include <QStringList>

#include "RPluginInterface.h"

class RScriptsPlugin : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qcad.scripts")
#endif

public:
    RScriptsPlugin() : RPluginInterface() {}
    virtual ~RScriptsPlugin() {}
    virtual bool init();
    virtual void uninit(bool) {}
    virtual void postInit(InitStatus) {}
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual void initTranslations();
    virtual RPluginInfo getPluginInfo();
    virtual bool checkLicense() { return true; }
};

#endif
