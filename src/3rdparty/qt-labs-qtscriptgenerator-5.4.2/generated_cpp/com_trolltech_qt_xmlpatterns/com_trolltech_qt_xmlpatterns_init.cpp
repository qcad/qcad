#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QSourceLocation_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPatternist_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPatternistSDK_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlQuery_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlNamePool_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_xmlpatterns_class_names[] = {
    "QSourceLocation"
    , "QPatternist"
    , "QPatternistSDK"
    , "QXmlQuery"
    , "QXmlNamePool"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_xmlpatterns_class_functions[] = {
    qtscript_create_QSourceLocation_class
    , qtscript_create_QPatternist_class
    , qtscript_create_QPatternistSDK_class
    , qtscript_create_QXmlQuery_class
    , qtscript_create_QXmlNamePool_class
};

void qtscript_initialize_com_trolltech_qt_xmlpatterns_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 5; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_xmlpatterns_class_names[i],
            qtscript_com_trolltech_qt_xmlpatterns_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
