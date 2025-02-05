#ifndef RDXFPLUGIN_H_
#define RDXFPLUGIN_H_

#include <QObject>

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
#if QT_VERSION < 0x060000
    virtual void initScriptExtensions(QScriptEngine&) {}
#endif
    virtual void initTranslations() {}
    virtual RPluginInfo getPluginInfo();
    virtual bool checkLicense() { return true; }
};

#endif
