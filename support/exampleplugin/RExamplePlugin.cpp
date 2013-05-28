#include "RExamplePlugin.h"
#include "RSettings.h"
#include "RPluginInfo.h"
#include "RVersion.h"

bool RExamplePlugin::init() {
    qDebug() << "RExamplePlugin::init";
    return true;
}

void RExamplePlugin::initScriptExtensions(QScriptEngine& engine) {
    Q_UNUSED(engine);
}

RPluginInfo RExamplePlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", R_QCAD_VERSION_STRING);
    ret.set("Name", "Example Plugin");
    ret.set("License", "GPLv3");
    ret.set("URL", "http://qcad.org");
    return ret;
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(example, RExamplePlugin)
QT_END_NAMESPACE
