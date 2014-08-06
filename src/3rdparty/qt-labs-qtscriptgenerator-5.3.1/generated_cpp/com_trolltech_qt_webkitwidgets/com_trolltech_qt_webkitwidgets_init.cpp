#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QGraphicsWebView_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ExtensionReturn_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebInspector_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebFrame_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebHitTestResult_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebView_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ChooseMultipleFilesExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ErrorPageExtensionOption_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ErrorPageExtensionReturn_class(QScriptEngine *engine);
QScriptValue qtscript_create_QWebPage_ChooseMultipleFilesExtensionReturn_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_webkitwidgets_class_names[] = {
    "QGraphicsWebView"
    , "QWebPage_ExtensionReturn"
    , "QWebInspector"
    , "QWebFrame"
    , "QWebHitTestResult"
    , "QWebView"
    , "QWebPage"
    , "QWebPage_ExtensionOption"
    , "QWebPage_ChooseMultipleFilesExtensionOption"
    , "QWebPage_ErrorPageExtensionOption"
    , "QWebPage_ErrorPageExtensionReturn"
    , "QWebPage_ChooseMultipleFilesExtensionReturn"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_webkitwidgets_class_functions[] = {
    qtscript_create_QGraphicsWebView_class
    , qtscript_create_QWebPage_ExtensionReturn_class
    , qtscript_create_QWebInspector_class
    , qtscript_create_QWebFrame_class
    , qtscript_create_QWebHitTestResult_class
    , qtscript_create_QWebView_class
    , qtscript_create_QWebPage_class
    , qtscript_create_QWebPage_ExtensionOption_class
    , qtscript_create_QWebPage_ChooseMultipleFilesExtensionOption_class
    , qtscript_create_QWebPage_ErrorPageExtensionOption_class
    , qtscript_create_QWebPage_ErrorPageExtensionReturn_class
    , qtscript_create_QWebPage_ChooseMultipleFilesExtensionReturn_class
};

void qtscript_initialize_com_trolltech_qt_webkitwidgets_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 12; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_webkitwidgets_class_names[i],
            qtscript_com_trolltech_qt_webkitwidgets_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
