#include <QtScript/QScriptExtensionPlugin>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtPlugin>
#include "plugin.h"


QStringList com_trolltech_qt_webkitwidgets_ScriptPlugin::keys() const
{
    QStringList list;
    list << QLatin1String("qt");
    list << QLatin1String("qt.webkitwidgets");
    return list;
}

void com_trolltech_qt_webkitwidgets_ScriptPlugin::initialize(const QString &key, QScriptEngine *engine)
{
    if (key == QLatin1String("qt")) {
    } else if (key == QLatin1String("qt.webkitwidgets")) {
        QScriptValue extensionObject = engine->globalObject();
        qtscript_initialize_com_trolltech_qt_webkitwidgets_bindings(extensionObject);
    } else {
        Q_ASSERT_X(false, "com_trolltech_qt_webkitwidgets::initialize", qPrintable(key));
    }
}

