#include "RExamplePlugin.h"

RPluginInfo RExamplePlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", "1.0");
    ret.set("ID", "EXAMPLE");
    ret.set("Name", "Example Plugin");
    ret.set("License", "GPLv3");
    ret.set("URL", "http://qcad.org");
    return ret;
}

#if QT_VERSION < 0x050000
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(example, RExamplePlugin)
QT_END_NAMESPACE
#endif
