#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdom.h>
#include <QVariant>
#include <qdom.h>
#include <qtextstream.h>

static const char * const qtscript_QDomNode_function_names[] = {
    "QDomNode"
    // static
    // prototype
    , "appendChild"
    , "childNodes"
    , "clear"
    , "cloneNode"
    , "columnNumber"
    , "firstChild"
    , "firstChildElement"
    , "hasAttributes"
    , "hasChildNodes"
    , "insertAfter"
    , "insertBefore"
    , "isAttr"
    , "isCDATASection"
    , "isCharacterData"
    , "isComment"
    , "isDocument"
    , "isDocumentFragment"
    , "isDocumentType"
    , "isElement"
    , "isEntity"
    , "isEntityReference"
    , "isNotation"
    , "isNull"
    , "isProcessingInstruction"
    , "isSupported"
    , "isText"
    , "lastChild"
    , "lastChildElement"
    , "lineNumber"
    , "localName"
    , "namedItem"
    , "namespaceURI"
    , "nextSibling"
    , "nextSiblingElement"
    , "nodeName"
    , "nodeType"
    , "nodeValue"
    , "normalize"
    , "equals"
    , "ownerDocument"
    , "parentNode"
    , "prefix"
    , "previousSibling"
    , "previousSiblingElement"
    , "removeChild"
    , "replaceChild"
    , "save"
    , "setNodeValue"
    , "setPrefix"
    , "toAttr"
    , "toCDATASection"
    , "toCharacterData"
    , "toComment"
    , "toDocument"
    , "toDocumentFragment"
    , "toDocumentType"
    , "toElement"
    , "toEntity"
    , "toEntityReference"
    , "toNotation"
    , "toProcessingInstruction"
    , "toText"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QDomNode_function_signatures[] = {
    "\nQDomNode arg__1"
    // static
    // prototype
    , "QDomNode newChild"
    , ""
    , ""
    , "bool deep"
    , ""
    , ""
    , "String tagName"
    , ""
    , ""
    , "QDomNode newChild, QDomNode refChild"
    , "QDomNode newChild, QDomNode refChild"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String feature, String version"
    , ""
    , ""
    , "String tagName"
    , ""
    , ""
    , "String name"
    , ""
    , ""
    , "String taName"
    , ""
    , ""
    , ""
    , ""
    , "QDomNode arg__1"
    , ""
    , ""
    , ""
    , ""
    , "String tagName"
    , "QDomNode oldChild"
    , "QDomNode newChild, QDomNode oldChild"
    , "QTextStream arg__1, int arg__2\nQTextStream arg__1, int arg__2, EncodingPolicy arg__3"
    , "String arg__1"
    , "String pre"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QTextStream arg__1"
""
};

static const int qtscript_QDomNode_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 2
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 2
    , 3
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QDomNode_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomNode::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomNode)
Q_DECLARE_METATYPE(QDomNode*)
Q_DECLARE_METATYPE(QDomNode::NodeType)
Q_DECLARE_METATYPE(QDomNode::EncodingPolicy)
Q_DECLARE_METATYPE(QDomNodeList)
Q_DECLARE_METATYPE(QDomElement)
Q_DECLARE_METATYPE(QDomDocument)
Q_DECLARE_METATYPE(QTextStream*)
Q_DECLARE_METATYPE(QDomAttr)
Q_DECLARE_METATYPE(QDomCDATASection)
Q_DECLARE_METATYPE(QDomCharacterData)
Q_DECLARE_METATYPE(QDomComment)
Q_DECLARE_METATYPE(QDomDocumentFragment)
Q_DECLARE_METATYPE(QDomDocumentType)
Q_DECLARE_METATYPE(QDomEntity)
Q_DECLARE_METATYPE(QDomEntityReference)
Q_DECLARE_METATYPE(QDomNotation)
Q_DECLARE_METATYPE(QDomProcessingInstruction)
Q_DECLARE_METATYPE(QDomText)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QDomNode::NodeType
//

static const QDomNode::NodeType qtscript_QDomNode_NodeType_values[] = {
    QDomNode::ElementNode
    , QDomNode::AttributeNode
    , QDomNode::TextNode
    , QDomNode::CDATASectionNode
    , QDomNode::EntityReferenceNode
    , QDomNode::EntityNode
    , QDomNode::ProcessingInstructionNode
    , QDomNode::CommentNode
    , QDomNode::DocumentNode
    , QDomNode::DocumentTypeNode
    , QDomNode::DocumentFragmentNode
    , QDomNode::NotationNode
    , QDomNode::BaseNode
    , QDomNode::CharacterDataNode
};

static const char * const qtscript_QDomNode_NodeType_keys[] = {
    "ElementNode"
    , "AttributeNode"
    , "TextNode"
    , "CDATASectionNode"
    , "EntityReferenceNode"
    , "EntityNode"
    , "ProcessingInstructionNode"
    , "CommentNode"
    , "DocumentNode"
    , "DocumentTypeNode"
    , "DocumentFragmentNode"
    , "NotationNode"
    , "BaseNode"
    , "CharacterDataNode"
};

static QString qtscript_QDomNode_NodeType_toStringHelper(QDomNode::NodeType value)
{
    for (int i = 0; i < 14; ++i) {
        if (qtscript_QDomNode_NodeType_values[i] == value)
            return QString::fromLatin1(qtscript_QDomNode_NodeType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QDomNode_NodeType_toScriptValue(QScriptEngine *engine, const QDomNode::NodeType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDomNode"));
    return clazz.property(qtscript_QDomNode_NodeType_toStringHelper(value));
}

static void qtscript_QDomNode_NodeType_fromScriptValue(const QScriptValue &value, QDomNode::NodeType &out)
{
    out = qvariant_cast<QDomNode::NodeType>(value.toVariant());
}

static QScriptValue qtscript_construct_QDomNode_NodeType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 14; ++i) {
        if (qtscript_QDomNode_NodeType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QDomNode::NodeType>(arg));
    }
    return context->throwError(QString::fromLatin1("NodeType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDomNode_NodeType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDomNode::NodeType value = qscriptvalue_cast<QDomNode::NodeType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDomNode_NodeType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDomNode::NodeType value = qscriptvalue_cast<QDomNode::NodeType>(context->thisObject());
    return QScriptValue(engine, qtscript_QDomNode_NodeType_toStringHelper(value));
}

static QScriptValue qtscript_create_QDomNode_NodeType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDomNode_NodeType,
        qtscript_QDomNode_NodeType_valueOf, qtscript_QDomNode_NodeType_toString);
    qScriptRegisterMetaType<QDomNode::NodeType>(engine, qtscript_QDomNode_NodeType_toScriptValue,
        qtscript_QDomNode_NodeType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 14; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDomNode_NodeType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDomNode_NodeType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDomNode::EncodingPolicy
//

static const QDomNode::EncodingPolicy qtscript_QDomNode_EncodingPolicy_values[] = {
    QDomNode::EncodingFromDocument
    , QDomNode::EncodingFromTextStream
};

static const char * const qtscript_QDomNode_EncodingPolicy_keys[] = {
    "EncodingFromDocument"
    , "EncodingFromTextStream"
};

static QString qtscript_QDomNode_EncodingPolicy_toStringHelper(QDomNode::EncodingPolicy value)
{
    if ((value >= QDomNode::EncodingFromDocument) && (value <= QDomNode::EncodingFromTextStream))
        return qtscript_QDomNode_EncodingPolicy_keys[static_cast<int>(value)-static_cast<int>(QDomNode::EncodingFromDocument)];
    return QString();
}

static QScriptValue qtscript_QDomNode_EncodingPolicy_toScriptValue(QScriptEngine *engine, const QDomNode::EncodingPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDomNode"));
    return clazz.property(qtscript_QDomNode_EncodingPolicy_toStringHelper(value));
}

static void qtscript_QDomNode_EncodingPolicy_fromScriptValue(const QScriptValue &value, QDomNode::EncodingPolicy &out)
{
    out = qvariant_cast<QDomNode::EncodingPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QDomNode_EncodingPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDomNode::EncodingFromDocument) && (arg <= QDomNode::EncodingFromTextStream))
        return qScriptValueFromValue(engine,  static_cast<QDomNode::EncodingPolicy>(arg));
    return context->throwError(QString::fromLatin1("EncodingPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDomNode_EncodingPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDomNode::EncodingPolicy value = qscriptvalue_cast<QDomNode::EncodingPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDomNode_EncodingPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDomNode::EncodingPolicy value = qscriptvalue_cast<QDomNode::EncodingPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QDomNode_EncodingPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QDomNode_EncodingPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDomNode_EncodingPolicy,
        qtscript_QDomNode_EncodingPolicy_valueOf, qtscript_QDomNode_EncodingPolicy_toString);
    qScriptRegisterMetaType<QDomNode::EncodingPolicy>(engine, qtscript_QDomNode_EncodingPolicy_toScriptValue,
        qtscript_QDomNode_EncodingPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDomNode_EncodingPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDomNode_EncodingPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDomNode
//

static QScriptValue qtscript_QDomNode_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 63;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDomNode* _q_self = qscriptvalue_cast<QDomNode*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomNode.%0(): this object is not a QDomNode")
            .arg(qtscript_QDomNode_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        QDomNode _q_result = _q_self->appendChild(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QDomNodeList _q_result = _q_self->childNodes();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QDomNode _q_result = _q_self->cloneNode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QDomNode _q_result = _q_self->cloneNode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QDomNode _q_result = _q_self->firstChild();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QDomElement _q_result = _q_self->firstChildElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomElement _q_result = _q_self->firstChildElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasAttributes();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasChildNodes();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        QDomNode _q_arg1 = qscriptvalue_cast<QDomNode>(context->argument(1));
        QDomNode _q_result = _q_self->insertAfter(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        QDomNode _q_arg1 = qscriptvalue_cast<QDomNode>(context->argument(1));
        QDomNode _q_result = _q_self->insertBefore(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAttr();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCDATASection();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCharacterData();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isComment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDocument();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDocumentFragment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDocumentType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isElement();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEntity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEntityReference();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNotation();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isProcessingInstruction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->isSupported(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QDomNode _q_result = _q_self->lastChild();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QDomElement _q_result = _q_self->lastChildElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomElement _q_result = _q_self->lastChildElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lineNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->localName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomNode _q_result = _q_self->namedItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->namespaceURI();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QDomNode _q_result = _q_self->nextSibling();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        QDomElement _q_result = _q_self->nextSiblingElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomElement _q_result = _q_self->nextSiblingElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->nodeName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        QDomNode::NodeType _q_result = _q_self->nodeType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->nodeValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        _q_self->normalize();
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 0) {
        QDomDocument _q_result = _q_self->ownerDocument();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 0) {
        QDomNode _q_result = _q_self->parentNode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->prefix();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        QDomNode _q_result = _q_self->previousSibling();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        QDomElement _q_result = _q_self->previousSiblingElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomElement _q_result = _q_self->previousSiblingElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        QDomNode _q_result = _q_self->removeChild(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 2) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        QDomNode _q_arg1 = qscriptvalue_cast<QDomNode>(context->argument(1));
        QDomNode _q_result = _q_self->replaceChild(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 2) {

                QTextStream & _q_arg0 = *qscriptvalue_cast<QTextStream*>(context->argument(0));
                        int _q_arg1 = context->argument(1).toInt32();
        _q_self->save(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {

                QTextStream & _q_arg0 = *qscriptvalue_cast<QTextStream*>(context->argument(0));
                        int _q_arg1 = context->argument(1).toInt32();
        QDomNode::EncodingPolicy _q_arg2 = qscriptvalue_cast<QDomNode::EncodingPolicy>(context->argument(2));
        _q_self->save(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setNodeValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPrefix(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QDomAttr _q_result = _q_self->toAttr();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        QDomCDATASection _q_result = _q_self->toCDATASection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        QDomCharacterData _q_result = _q_self->toCharacterData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        QDomComment _q_result = _q_self->toComment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 0) {
        QDomDocument _q_result = _q_self->toDocument();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 54:
    if (context->argumentCount() == 0) {
        QDomDocumentFragment _q_result = _q_self->toDocumentFragment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 0) {
        QDomDocumentType _q_result = _q_self->toDocumentType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 56:
    if (context->argumentCount() == 0) {
        QDomElement _q_result = _q_self->toElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 57:
    if (context->argumentCount() == 0) {
        QDomEntity _q_result = _q_self->toEntity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 58:
    if (context->argumentCount() == 0) {
        QDomEntityReference _q_result = _q_self->toEntityReference();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 59:
    if (context->argumentCount() == 0) {
        QDomNotation _q_result = _q_self->toNotation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 60:
    if (context->argumentCount() == 0) {
        QDomProcessingInstruction _q_result = _q_self->toProcessingInstruction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 61:
    if (context->argumentCount() == 0) {
        QDomText _q_result = _q_self->toText();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 62:
    if (context->argumentCount() == 1) {
        QTextStream* _q_arg0 = qscriptvalue_cast<QTextStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 63: {
    QString result = QString::fromLatin1("QDomNode");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomNode_throw_ambiguity_error_helper(context,
        qtscript_QDomNode_function_names[_id+1],
        qtscript_QDomNode_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomNode_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomNode(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomNode _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomNode _q_arg0 = qscriptvalue_cast<QDomNode>(context->argument(0));
        QDomNode _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomNode_throw_ambiguity_error_helper(context,
        qtscript_QDomNode_function_names[_id],
        qtscript_QDomNode_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomNode_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomNode*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomNode*)0));
    for (int i = 0; i < 64; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomNode_prototype_call, qtscript_QDomNode_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomNode_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomNode>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomNode*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomNode_static_call, proto, qtscript_QDomNode_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("NodeType"),
        qtscript_create_QDomNode_NodeType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("EncodingPolicy"),
        qtscript_create_QDomNode_EncodingPolicy_class(engine, ctor));
    return ctor;
}
