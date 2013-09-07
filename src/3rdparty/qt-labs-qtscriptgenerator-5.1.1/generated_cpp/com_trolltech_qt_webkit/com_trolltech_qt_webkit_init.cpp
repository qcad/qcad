#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QWebPluginFactory_Plugin_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebElement_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_ExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebSettings_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_MimeType_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_ExtensionReturn_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebHistoryInterface_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_webkit_class_names[] = {
    "QWebPluginFactory_Plugin"
    , "QWebElement"
    , "QWebPluginFactory_ExtensionOption"
    , "QWebSettings"
    , "QWebPluginFactory_MimeType"
    , "QWebPluginFactory_ExtensionReturn"
    , "QWebPluginFactory"
    , "QWebHistoryInterface"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_webkit_class_functions[] = {
    qtscript_create_QWebPluginFactory_Plugin_class
    , qtscript_create_QWebElement_class
    , qtscript_create_QWebPluginFactory_ExtensionOption_class
    , qtscript_create_QWebSettings_class
    , qtscript_create_QWebPluginFactory_MimeType_class
    , qtscript_create_QWebPluginFactory_ExtensionReturn_class
    , qtscript_create_QWebPluginFactory_class
    , qtscript_create_QWebHistoryInterface_class
};

void qtscript_initialize_com_trolltech_qt_webkit_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 8; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_webkit_class_names[i],
            qtscript_com_trolltech_qt_webkit_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
