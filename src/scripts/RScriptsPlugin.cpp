#include <QTime>

#include "RGuiAction.h"
#include "RPluginLoader.h"
#include "RScriptsPlugin.h"
#include "RS.h"
#include "RSettings.h"
#include "RVersion.h"

bool RScriptsPlugin::init() {
#ifdef QT_DEBUG
    qDebug() << "RScriptsPlugin::init";
#endif

    return true;
}

void RScriptsPlugin::initScriptExtensions(QScriptEngine& engine) {
    Q_UNUSED(engine)
}

void RScriptsPlugin::initTranslations() {
    RSettings::loadTranslations("scripts", QStringList() << ":ts");
}

RPluginInfo RScriptsPlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", R_QCAD_VERSION_STRING);
    ret.set("ID", "SCRIPTS");
    ret.set("Name", "QCAD Scripts");
    ret.set("Description", "QCAD Scripts.");
    ret.set("License", "GPLv3");
    ret.set("URL", "http://qcad.org");

    ret.set("OverridePriority", "0");
    ret.set("NameOverride", "QCAD");
    return ret;
}

#if QT_VERSION < 0x050000
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(scripts, RScriptsPlugin)
QT_END_NAMESPACE
#endif
