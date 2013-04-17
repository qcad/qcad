#include <QtPlugin>

#include "RDxfExporterFactory.h"
#include "RDxfImporterFactory.h"
#include "RDxfPlugin.h"
#include "RPluginInfo.h"

bool RDxfPlugin::init() {
    qDebug() << "RDxfPlugin::init";
    RDxfImporterFactory::registerFileImporter();
    RDxfExporterFactory::registerFileExporter();
    return true;
}

RPluginInfo RDxfPlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.setVersionString(QString("3.0.11 (dxflib %1, Qt %2)").arg(DL_VERSION).arg(qVersion()));
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
