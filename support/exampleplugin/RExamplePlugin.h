#include <QDebug>
#include <QObject>
#include <QScriptEngine>
#include <QStringList>

#include "RPluginInterface.h"

class RExamplePlugin : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)

public:
    virtual bool init();
    virtual void uninit(bool) {}
    virtual void postInit() {}
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual RPluginInfo getPluginInfo();
};
