#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QXmlQuery_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractXmlNodeModel_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlItem_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPatternistSDK_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSourceLocation_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlNodeModelIndex_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractXmlReceiver_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlSchema_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlName_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlNamePool_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlResultItems_class(QScriptEngine *engine);
QScriptValue qtscript_create_QPatternist_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlSchemaValidator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSimpleXmlNodeModel_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlSerializer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractMessageHandler_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractUriResolver_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlFormatter_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_xmlpatterns_class_names[] = {
    "QXmlQuery"
    , "QAbstractXmlNodeModel"
    , "QXmlItem"
    , "QPatternistSDK"
    , "QSourceLocation"
    , "QXmlNodeModelIndex"
    , "QAbstractXmlReceiver"
    , "QXmlSchema"
    , "QXmlName"
    , "QXmlNamePool"
    , "QXmlResultItems"
    , "QPatternist"
    , "QXmlSchemaValidator"
    , "QSimpleXmlNodeModel"
    , "QXmlSerializer"
    , "QAbstractMessageHandler"
    , "QAbstractUriResolver"
    , "QXmlFormatter"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_xmlpatterns_class_functions[] = {
    qtscript_create_QXmlQuery_class
    , qtscript_create_QAbstractXmlNodeModel_class
    , qtscript_create_QXmlItem_class
    , qtscript_create_QPatternistSDK_class
    , qtscript_create_QSourceLocation_class
    , qtscript_create_QXmlNodeModelIndex_class
    , qtscript_create_QAbstractXmlReceiver_class
    , qtscript_create_QXmlSchema_class
    , qtscript_create_QXmlName_class
    , qtscript_create_QXmlNamePool_class
    , qtscript_create_QXmlResultItems_class
    , qtscript_create_QPatternist_class
    , qtscript_create_QXmlSchemaValidator_class
    , qtscript_create_QSimpleXmlNodeModel_class
    , qtscript_create_QXmlSerializer_class
    , qtscript_create_QAbstractMessageHandler_class
    , qtscript_create_QAbstractUriResolver_class
    , qtscript_create_QXmlFormatter_class
};

void qtscript_initialize_com_trolltech_qt_xmlpatterns_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 18; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_xmlpatterns_class_names[i],
            qtscript_com_trolltech_qt_xmlpatterns_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
