#include <QObject>
#include <QScriptEngine>

#include "RPluginInterface.h"

class RExamplePlugin : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qcad.exampleplugin")
#endif

public:
    virtual bool init() { return true; }
    virtual void uninit(bool) {}
    virtual void postInit(InitStatus) {}
    virtual void initScriptExtensions(QScriptEngine&) {}
    virtual RPluginInfo getPluginInfo();
    virtual bool checkLicense() { return true; }
    virtual void initTranslations(){}
};

