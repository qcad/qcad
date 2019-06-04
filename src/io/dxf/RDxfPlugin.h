#ifndef RDXFPLUGIN_H_
#define RDXFPLUGIN_H_

#include <QDebug>
#include <QObject>
#include <QStringList>

#include "RPluginInterface.h"

class RSpline;

/**
 * \ingroup dxf
 */
class RDxfPlugin : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qcad.dxf")
#endif

public:
    virtual bool init();
    virtual void uninit(bool) {}
    virtual void postInit(InitStatus) {}
    virtual void initScriptExtensions(QScriptEngine&) {}
    virtual void initTranslations() {}
    virtual RPluginInfo getPluginInfo();
    virtual bool checkLicense() { return true; }
};

#endif
