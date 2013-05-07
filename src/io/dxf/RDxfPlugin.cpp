#include <QtPlugin>

#include "RDxfExporterFactory.h"
#include "RDxfImporterFactory.h"
#include "RDxfPlugin.h"
#include "RPluginInfo.h"
#include "RSettings.h"

bool RDxfPlugin::init() {
    qDebug() << "RDxfPlugin::init";
    RDxfImporterFactory::registerFileImporter();
    RDxfExporterFactory::registerFileExporter();
    return true;
}

RPluginInfo RDxfPlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.setVersionString(QString("%1 (dxflib %2)").arg(RSettings::getVersionString()).arg(DL_VERSION));
    ret.setAboutString("DXF Plugin");
    ret.setDescription(
        QString(
            "Import support for the DXF format. "
            "Based on dxflib."
        )
    );
    ret.setLicense("GPLv2");
    ret.setUrl("http://www.ribbonsoft.com");
    return ret;
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(qcaddwg, RDxfPlugin)
QT_END_NAMESPACE
