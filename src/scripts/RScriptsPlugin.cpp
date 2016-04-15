#include "RScriptsPlugin.h"
#include "RSettings.h"

void RScriptsPlugin::initScriptExtensions(QScriptEngine& engine) {
    Q_UNUSED(engine)
}

bool RScriptsPlugin::init() {
    qDebug() << "RScriptsPlugin::init";
    return true;
}

void RScriptsPlugin::postInit(InitStatus status) {
}

void RScriptsPlugin::uninit(bool remove) {
    Q_UNUSED(remove)

    qDebug() << "RScriptsPlugin::uninit";
}

RPluginInfo RScriptsPlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", RSettings::getVersionString());
    ret.set("ID", "SCRIPTS");
    ret.set("Name", "QCAD Scripts");
    ret.set("Description",  "QCAD Scripts Plugin.");
    ret.set("License", "GPLv3");
    ret.set("URL", "http://qcad.org");
    return ret;
}

#if QT_VERSION < 0x050000
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(scripts, RScriptsPlugin)
QT_END_NAMESPACE
#endif
