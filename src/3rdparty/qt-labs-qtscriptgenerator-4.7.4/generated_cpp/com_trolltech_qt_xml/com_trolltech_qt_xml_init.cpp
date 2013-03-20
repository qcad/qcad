#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QXmlDTDHandler_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlReader_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlContentHandler_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlAttributes_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomNode_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomNodeList_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomNamedNodeMap_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlEntityResolver_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlErrorHandler_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlLexicalHandler_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlDeclHandler_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomImplementation_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlInputSource_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlParseException_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlLocator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomDocument_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomEntityReference_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomCharacterData_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomDocumentFragment_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomEntity_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomDocumentType_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomElement_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomNotation_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlDefaultHandler_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomProcessingInstruction_class(QScriptEngine *engine);
QScriptValue qtscript_create_QXmlSimpleReader_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomAttr_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomComment_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomText_class(QScriptEngine *engine);
QScriptValue qtscript_create_QDomCDATASection_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_xml_class_names[] = {
    "QXmlDTDHandler"
    , "QXmlReader"
    , "QXmlContentHandler"
    , "QXmlAttributes"
    , "QDomNode"
    , "QDomNodeList"
    , "QDomNamedNodeMap"
    , "QXmlEntityResolver"
    , "QXmlErrorHandler"
    , "QXmlLexicalHandler"
    , "QXmlDeclHandler"
    , "QDomImplementation"
    , "QXmlInputSource"
    , "QXmlParseException"
    , "QXmlLocator"
    , "QDomDocument"
    , "QDomEntityReference"
    , "QDomCharacterData"
    , "QDomDocumentFragment"
    , "QDomEntity"
    , "QDomDocumentType"
    , "QDomElement"
    , "QDomNotation"
    , "QXmlDefaultHandler"
    , "QDomProcessingInstruction"
    , "QXmlSimpleReader"
    , "QDomAttr"
    , "QDomComment"
    , "QDomText"
    , "QDomCDATASection"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_xml_class_functions[] = {
    qtscript_create_QXmlDTDHandler_class
    , qtscript_create_QXmlReader_class
    , qtscript_create_QXmlContentHandler_class
    , qtscript_create_QXmlAttributes_class
    , qtscript_create_QDomNode_class
    , qtscript_create_QDomNodeList_class
    , qtscript_create_QDomNamedNodeMap_class
    , qtscript_create_QXmlEntityResolver_class
    , qtscript_create_QXmlErrorHandler_class
    , qtscript_create_QXmlLexicalHandler_class
    , qtscript_create_QXmlDeclHandler_class
    , qtscript_create_QDomImplementation_class
    , qtscript_create_QXmlInputSource_class
    , qtscript_create_QXmlParseException_class
    , qtscript_create_QXmlLocator_class
    , qtscript_create_QDomDocument_class
    , qtscript_create_QDomEntityReference_class
    , qtscript_create_QDomCharacterData_class
    , qtscript_create_QDomDocumentFragment_class
    , qtscript_create_QDomEntity_class
    , qtscript_create_QDomDocumentType_class
    , qtscript_create_QDomElement_class
    , qtscript_create_QDomNotation_class
    , qtscript_create_QXmlDefaultHandler_class
    , qtscript_create_QDomProcessingInstruction_class
    , qtscript_create_QXmlSimpleReader_class
    , qtscript_create_QDomAttr_class
    , qtscript_create_QDomComment_class
    , qtscript_create_QDomText_class
    , qtscript_create_QDomCDATASection_class
};

void qtscript_initialize_com_trolltech_qt_xml_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 30; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_xml_class_names[i],
            qtscript_com_trolltech_qt_xml_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
