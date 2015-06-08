#include <QtScript/QScriptExtensionPlugin>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

void qtscript_initialize_com_trolltech_qt_widgets_bindings(QScriptValue &);

class com_trolltech_qt_widgets_ScriptPlugin : public QScriptExtensionPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "com_trolltech_qt_widgets_ScriptPlugin")
public:
    QStringList keys() const;
    void initialize(const QString &key, QScriptEngine *engine);
};


