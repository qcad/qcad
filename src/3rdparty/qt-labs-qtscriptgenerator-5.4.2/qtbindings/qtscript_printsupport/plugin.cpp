#include <QtScript/QScriptExtensionPlugin>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include "plugin.h"

QStringList com_trolltech_qt_printsupport_ScriptPlugin::keys() const
{
    QStringList list;
    list << QLatin1String("qt");
    list << QLatin1String("qt.printsupport");
    return list;
}

void com_trolltech_qt_printsupport_ScriptPlugin::initialize(const QString &key, QScriptEngine *engine)
{
    if (key == QLatin1String("qt")) {
    } else if (key == QLatin1String("qt.printsupport")) {
        QScriptValue extensionObject = engine->globalObject();
        qtscript_initialize_com_trolltech_qt_printsupport_bindings(extensionObject);
    } else {
        Q_ASSERT_X(false, "com_trolltech_qt_printsupport::initialize", qPrintable(key));
    }
}

