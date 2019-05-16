#include <QtPlugin>

#include "RDxfExporterFactory.h"
#include "RDxfImporterFactory.h"
#include "RDxfPlugin.h"
#include "RSettings.h"

bool RDxfPlugin::init() {
    //qDebug() << "RDxfPlugin::init";
    RDxfImporterFactory::registerFileImporter();
    RDxfExporterFactory::registerFileExporter();
    return true;
}

RPluginInfo RDxfPlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", QString("%1 (dxflib %2)").arg(RSettings::getVersionString()).arg(DL_VERSION));
    ret.set("ID", "DXF");
    ret.set("Name", "DXF");
    ret.set("Description",
        QString(
            "Import/export support for the DXF format. "
            "Based on dxflib."
        )
    );
    ret.set("License", "GPLv2+");
    ret.set("URL", "http://www.qcad.org");
    return ret;
}

#if QT_VERSION < 0x050000
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(qcaddxf, RDxfPlugin)
QT_END_NAMESPACE
#endif
