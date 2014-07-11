#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QWebElement_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_MimeType_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_Plugin_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ExtensionReturn_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_ExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_ExtensionReturn_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebHitTestResult_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebSettings_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ErrorPageExtensionReturn_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebFrame_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ChooseMultipleFilesExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebHistoryInterface_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ErrorPageExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ChooseMultipleFilesExtensionReturn_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPluginFactory_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebView_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebInspector_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGraphicsWebView_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_webkit_class_names[] = {
    "QWebElement"
    , "QWebPluginFactory_MimeType"
    , "QWebPluginFactory_Plugin"
    , "QWebPage_ExtensionReturn"
    , "QWebPluginFactory_ExtensionOption"
    , "QWebPage_ExtensionOption"
    , "QWebPluginFactory_ExtensionReturn"
    , "QWebHitTestResult"
    , "QWebSettings"
    , "QWebPage_ErrorPageExtensionReturn"
    , "QWebPage"
    , "QWebFrame"
    , "QWebPage_ChooseMultipleFilesExtensionOption"
    , "QWebHistoryInterface"
    , "QWebPage_ErrorPageExtensionOption"
    , "QWebPage_ChooseMultipleFilesExtensionReturn"
    , "QWebPluginFactory"
    , "QWebView"
    , "QWebInspector"
    , "QGraphicsWebView"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_webkit_class_functions[] = {
    qtscript_create_QWebElement_class
    , qtscript_create_QWebPluginFactory_MimeType_class
    , qtscript_create_QWebPluginFactory_Plugin_class
    , qtscript_create_QWebPage_ExtensionReturn_class
    , qtscript_create_QWebPluginFactory_ExtensionOption_class
    , qtscript_create_QWebPage_ExtensionOption_class
    , qtscript_create_QWebPluginFactory_ExtensionReturn_class
    , qtscript_create_QWebHitTestResult_class
    , qtscript_create_QWebSettings_class
    , qtscript_create_QWebPage_ErrorPageExtensionReturn_class
    , qtscript_create_QWebPage_class
    , qtscript_create_QWebFrame_class
    , qtscript_create_QWebPage_ChooseMultipleFilesExtensionOption_class
    , qtscript_create_QWebHistoryInterface_class
    , qtscript_create_QWebPage_ErrorPageExtensionOption_class
    , qtscript_create_QWebPage_ChooseMultipleFilesExtensionReturn_class
    , qtscript_create_QWebPluginFactory_class
    , qtscript_create_QWebView_class
    , qtscript_create_QWebInspector_class
    , qtscript_create_QGraphicsWebView_class
};

void qtscript_initialize_com_trolltech_qt_webkit_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 20; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_webkit_class_names[i],
            qtscript_com_trolltech_qt_webkit_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
