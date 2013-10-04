#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlstream.h>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qvector.h>
#include <qxmlstream.h>

static const char * const qtscript_QXmlStreamReader_function_names[] = {
    "QXmlStreamReader"
    // static
    // prototype
    , "addData"
    , "addExtraNamespaceDeclaration"
    , "addExtraNamespaceDeclarations"
    , "atEnd"
    , "attributes"
    , "characterOffset"
    , "clear"
    , "columnNumber"
    , "device"
    , "documentEncoding"
    , "documentVersion"
    , "dtdName"
    , "dtdPublicId"
    , "dtdSystemId"
    , "entityDeclarations"
    , "entityResolver"
    , "error"
    , "errorString"
    , "hasError"
    , "isCDATA"
    , "isCharacters"
    , "isComment"
    , "isDTD"
    , "isEndDocument"
    , "isEndElement"
    , "isEntityReference"
    , "isProcessingInstruction"
    , "isStandaloneDocument"
    , "isStartDocument"
    , "isStartElement"
    , "isWhitespace"
    , "lineNumber"
    , "name"
    , "namespaceDeclarations"
    , "namespaceProcessing"
    , "namespaceUri"
    , "notationDeclarations"
    , "prefix"
    , "processingInstructionData"
    , "processingInstructionTarget"
    , "qualifiedName"
    , "raiseError"
    , "readElementText"
    , "readNext"
    , "readNextStartElement"
    , "setDevice"
    , "setEntityResolver"
    , "setNamespaceProcessing"
    , "skipCurrentElement"
    , "text"
    , "tokenString"
    , "tokenType"
    , "toString"
};

static const char * const qtscript_QXmlStreamReader_function_signatures[] = {
    "\nQIODevice device\nQByteArray data\nString data"
    // static
    // prototype
    , "QByteArray data\nString data"
    , "QXmlStreamNamespaceDeclaration extraNamespaceDeclaraction"
    , "List extraNamespaceDeclaractions"
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
    , "String message"
    , "\nReadElementTextBehaviour behaviour"
    , ""
    , ""
    , "QIODevice device"
    , "QXmlStreamEntityResolver resolver"
    , "bool arg__1"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QXmlStreamReader_function_lengths[] = {
    1
    // static
    // prototype
    , 1
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
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QXmlStreamReader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlStreamReader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlStreamReader*)
Q_DECLARE_METATYPE(QXmlStreamReader::Error)
Q_DECLARE_METATYPE(QXmlStreamReader::TokenType)
Q_DECLARE_METATYPE(QXmlStreamReader::ReadElementTextBehaviour)
Q_DECLARE_METATYPE(QXmlStreamNamespaceDeclaration)
Q_DECLARE_METATYPE(QVector<QXmlStreamNamespaceDeclaration>)
Q_DECLARE_METATYPE(QXmlStreamAttributes)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QStringRef)
Q_DECLARE_METATYPE(QXmlStreamEntityDeclaration)
Q_DECLARE_METATYPE(QVector<QXmlStreamEntityDeclaration>)
Q_DECLARE_METATYPE(QXmlStreamEntityResolver*)
Q_DECLARE_METATYPE(QXmlStreamNotationDeclaration)
Q_DECLARE_METATYPE(QVector<QXmlStreamNotationDeclaration>)

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
// QXmlStreamReader::Error
//

static const QXmlStreamReader::Error qtscript_QXmlStreamReader_Error_values[] = {
    QXmlStreamReader::NoError
    , QXmlStreamReader::UnexpectedElementError
    , QXmlStreamReader::CustomError
    , QXmlStreamReader::NotWellFormedError
    , QXmlStreamReader::PrematureEndOfDocumentError
};

static const char * const qtscript_QXmlStreamReader_Error_keys[] = {
    "NoError"
    , "UnexpectedElementError"
    , "CustomError"
    , "NotWellFormedError"
    , "PrematureEndOfDocumentError"
};

static QString qtscript_QXmlStreamReader_Error_toStringHelper(QXmlStreamReader::Error value)
{
    if ((value >= QXmlStreamReader::NoError) && (value <= QXmlStreamReader::PrematureEndOfDocumentError))
        return qtscript_QXmlStreamReader_Error_keys[static_cast<int>(value)-static_cast<int>(QXmlStreamReader::NoError)];
    return QString();
}

static QScriptValue qtscript_QXmlStreamReader_Error_toScriptValue(QScriptEngine *engine, const QXmlStreamReader::Error &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QXmlStreamReader"));
    return clazz.property(qtscript_QXmlStreamReader_Error_toStringHelper(value));
}

static void qtscript_QXmlStreamReader_Error_fromScriptValue(const QScriptValue &value, QXmlStreamReader::Error &out)
{
    out = qvariant_cast<QXmlStreamReader::Error>(value.toVariant());
}

static QScriptValue qtscript_construct_QXmlStreamReader_Error(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QXmlStreamReader::NoError) && (arg <= QXmlStreamReader::PrematureEndOfDocumentError))
        return qScriptValueFromValue(engine,  static_cast<QXmlStreamReader::Error>(arg));
    return context->throwError(QString::fromLatin1("Error(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QXmlStreamReader_Error_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QXmlStreamReader::Error value = qscriptvalue_cast<QXmlStreamReader::Error>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QXmlStreamReader_Error_toString(QScriptContext *context, QScriptEngine *engine)
{
    QXmlStreamReader::Error value = qscriptvalue_cast<QXmlStreamReader::Error>(context->thisObject());
    return QScriptValue(engine, qtscript_QXmlStreamReader_Error_toStringHelper(value));
}

static QScriptValue qtscript_create_QXmlStreamReader_Error_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QXmlStreamReader_Error,
        qtscript_QXmlStreamReader_Error_valueOf, qtscript_QXmlStreamReader_Error_toString);
    qScriptRegisterMetaType<QXmlStreamReader::Error>(engine, qtscript_QXmlStreamReader_Error_toScriptValue,
        qtscript_QXmlStreamReader_Error_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QXmlStreamReader_Error_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QXmlStreamReader_Error_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QXmlStreamReader::TokenType
//

static const QXmlStreamReader::TokenType qtscript_QXmlStreamReader_TokenType_values[] = {
    QXmlStreamReader::NoToken
    , QXmlStreamReader::Invalid
    , QXmlStreamReader::StartDocument
    , QXmlStreamReader::EndDocument
    , QXmlStreamReader::StartElement
    , QXmlStreamReader::EndElement
    , QXmlStreamReader::Characters
    , QXmlStreamReader::Comment
    , QXmlStreamReader::DTD
    , QXmlStreamReader::EntityReference
    , QXmlStreamReader::ProcessingInstruction
};

static const char * const qtscript_QXmlStreamReader_TokenType_keys[] = {
    "NoToken"
    , "Invalid"
    , "StartDocument"
    , "EndDocument"
    , "StartElement"
    , "EndElement"
    , "Characters"
    , "Comment"
    , "DTD"
    , "EntityReference"
    , "ProcessingInstruction"
};

static QString qtscript_QXmlStreamReader_TokenType_toStringHelper(QXmlStreamReader::TokenType value)
{
    if ((value >= QXmlStreamReader::NoToken) && (value <= QXmlStreamReader::ProcessingInstruction))
        return qtscript_QXmlStreamReader_TokenType_keys[static_cast<int>(value)-static_cast<int>(QXmlStreamReader::NoToken)];
    return QString();
}

static QScriptValue qtscript_QXmlStreamReader_TokenType_toScriptValue(QScriptEngine *engine, const QXmlStreamReader::TokenType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QXmlStreamReader"));
    return clazz.property(qtscript_QXmlStreamReader_TokenType_toStringHelper(value));
}

static void qtscript_QXmlStreamReader_TokenType_fromScriptValue(const QScriptValue &value, QXmlStreamReader::TokenType &out)
{
    out = qvariant_cast<QXmlStreamReader::TokenType>(value.toVariant());
}

static QScriptValue qtscript_construct_QXmlStreamReader_TokenType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QXmlStreamReader::NoToken) && (arg <= QXmlStreamReader::ProcessingInstruction))
        return qScriptValueFromValue(engine,  static_cast<QXmlStreamReader::TokenType>(arg));
    return context->throwError(QString::fromLatin1("TokenType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QXmlStreamReader_TokenType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QXmlStreamReader::TokenType value = qscriptvalue_cast<QXmlStreamReader::TokenType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QXmlStreamReader_TokenType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QXmlStreamReader::TokenType value = qscriptvalue_cast<QXmlStreamReader::TokenType>(context->thisObject());
    return QScriptValue(engine, qtscript_QXmlStreamReader_TokenType_toStringHelper(value));
}

static QScriptValue qtscript_create_QXmlStreamReader_TokenType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QXmlStreamReader_TokenType,
        qtscript_QXmlStreamReader_TokenType_valueOf, qtscript_QXmlStreamReader_TokenType_toString);
    qScriptRegisterMetaType<QXmlStreamReader::TokenType>(engine, qtscript_QXmlStreamReader_TokenType_toScriptValue,
        qtscript_QXmlStreamReader_TokenType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QXmlStreamReader_TokenType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QXmlStreamReader_TokenType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QXmlStreamReader::ReadElementTextBehaviour
//

static const QXmlStreamReader::ReadElementTextBehaviour qtscript_QXmlStreamReader_ReadElementTextBehaviour_values[] = {
    QXmlStreamReader::ErrorOnUnexpectedElement
    , QXmlStreamReader::IncludeChildElements
    , QXmlStreamReader::SkipChildElements
};

static const char * const qtscript_QXmlStreamReader_ReadElementTextBehaviour_keys[] = {
    "ErrorOnUnexpectedElement"
    , "IncludeChildElements"
    , "SkipChildElements"
};

static QString qtscript_QXmlStreamReader_ReadElementTextBehaviour_toStringHelper(QXmlStreamReader::ReadElementTextBehaviour value)
{
    if ((value >= QXmlStreamReader::ErrorOnUnexpectedElement) && (value <= QXmlStreamReader::SkipChildElements))
        return qtscript_QXmlStreamReader_ReadElementTextBehaviour_keys[static_cast<int>(value)-static_cast<int>(QXmlStreamReader::ErrorOnUnexpectedElement)];
    return QString();
}

static QScriptValue qtscript_QXmlStreamReader_ReadElementTextBehaviour_toScriptValue(QScriptEngine *engine, const QXmlStreamReader::ReadElementTextBehaviour &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QXmlStreamReader"));
    return clazz.property(qtscript_QXmlStreamReader_ReadElementTextBehaviour_toStringHelper(value));
}

static void qtscript_QXmlStreamReader_ReadElementTextBehaviour_fromScriptValue(const QScriptValue &value, QXmlStreamReader::ReadElementTextBehaviour &out)
{
    out = qvariant_cast<QXmlStreamReader::ReadElementTextBehaviour>(value.toVariant());
}

static QScriptValue qtscript_construct_QXmlStreamReader_ReadElementTextBehaviour(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QXmlStreamReader::ErrorOnUnexpectedElement) && (arg <= QXmlStreamReader::SkipChildElements))
        return qScriptValueFromValue(engine,  static_cast<QXmlStreamReader::ReadElementTextBehaviour>(arg));
    return context->throwError(QString::fromLatin1("ReadElementTextBehaviour(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QXmlStreamReader_ReadElementTextBehaviour_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QXmlStreamReader::ReadElementTextBehaviour value = qscriptvalue_cast<QXmlStreamReader::ReadElementTextBehaviour>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QXmlStreamReader_ReadElementTextBehaviour_toString(QScriptContext *context, QScriptEngine *engine)
{
    QXmlStreamReader::ReadElementTextBehaviour value = qscriptvalue_cast<QXmlStreamReader::ReadElementTextBehaviour>(context->thisObject());
    return QScriptValue(engine, qtscript_QXmlStreamReader_ReadElementTextBehaviour_toStringHelper(value));
}

static QScriptValue qtscript_create_QXmlStreamReader_ReadElementTextBehaviour_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QXmlStreamReader_ReadElementTextBehaviour,
        qtscript_QXmlStreamReader_ReadElementTextBehaviour_valueOf, qtscript_QXmlStreamReader_ReadElementTextBehaviour_toString);
    qScriptRegisterMetaType<QXmlStreamReader::ReadElementTextBehaviour>(engine, qtscript_QXmlStreamReader_ReadElementTextBehaviour_toScriptValue,
        qtscript_QXmlStreamReader_ReadElementTextBehaviour_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QXmlStreamReader_ReadElementTextBehaviour_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QXmlStreamReader_ReadElementTextBehaviour_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QXmlStreamReader
//

static QScriptValue qtscript_QXmlStreamReader_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 52;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlStreamReader* _q_self = qscriptvalue_cast<QXmlStreamReader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlStreamReader.%0(): this object is not a QXmlStreamReader")
            .arg(qtscript_QXmlStreamReader_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            _q_self->addData(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->addData(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QXmlStreamNamespaceDeclaration _q_arg0 = qscriptvalue_cast<QXmlStreamNamespaceDeclaration>(context->argument(0));
        _q_self->addExtraNamespaceDeclaration(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QVector<QXmlStreamNamespaceDeclaration> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->addExtraNamespaceDeclarations(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->atEnd();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QXmlStreamAttributes _q_result = _q_self->attributes();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->characterOffset();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->columnNumber();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->documentEncoding();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->documentVersion();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->dtdName();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->dtdPublicId();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->dtdSystemId();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QVector<QXmlStreamEntityDeclaration> _q_result = _q_self->entityDeclarations();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QXmlStreamEntityResolver* _q_result = _q_self->entityResolver();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QXmlStreamReader::Error _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasError();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCDATA();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCharacters();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isComment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDTD();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEndDocument();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEndElement();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEntityReference();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isProcessingInstruction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isStandaloneDocument();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isStartDocument();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isStartElement();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWhitespace();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->lineNumber();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->name();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        QVector<QXmlStreamNamespaceDeclaration> _q_result = _q_self->namespaceDeclarations();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->namespaceProcessing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->namespaceUri();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QVector<QXmlStreamNotationDeclaration> _q_result = _q_self->notationDeclarations();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->prefix();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 38:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->processingInstructionData();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 39:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->processingInstructionTarget();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 40:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->qualifiedName();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        _q_self->raiseError();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->raiseError(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->readElementText();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QXmlStreamReader::ReadElementTextBehaviour _q_arg0 = qscriptvalue_cast<QXmlStreamReader::ReadElementTextBehaviour>(context->argument(0));
        QString _q_result = _q_self->readElementText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        QXmlStreamReader::TokenType _q_result = _q_self->readNext();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->readNextStartElement();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        QXmlStreamEntityResolver* _q_arg0 = qscriptvalue_cast<QXmlStreamEntityResolver*>(context->argument(0));
        _q_self->setEntityResolver(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setNamespaceProcessing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        _q_self->skipCurrentElement();
        return context->engine()->undefinedValue();
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->text();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->tokenString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        QXmlStreamReader::TokenType _q_result = _q_self->tokenType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52: {
    QString result = QString::fromLatin1("QXmlStreamReader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamReader_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamReader_function_names[_id+1],
        qtscript_QXmlStreamReader_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlStreamReader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlStreamReader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlStreamReader* _q_cpp_result = new QXmlStreamReader();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QXmlStreamReader* _q_cpp_result = new QXmlStreamReader(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QXmlStreamReader* _q_cpp_result = new QXmlStreamReader(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QXmlStreamReader* _q_cpp_result = new QXmlStreamReader(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamReader_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamReader_function_names[_id],
        qtscript_QXmlStreamReader_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlStreamReader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamReader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlStreamReader*)0));
    for (int i = 0; i < 53; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamReader_prototype_call, qtscript_QXmlStreamReader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlStreamReader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamReader*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlStreamReader_static_call, proto, qtscript_QXmlStreamReader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Error"),
        qtscript_create_QXmlStreamReader_Error_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TokenType"),
        qtscript_create_QXmlStreamReader_TokenType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ReadElementTextBehaviour"),
        qtscript_create_QXmlStreamReader_ReadElementTextBehaviour_class(engine, ctor));
    return ctor;
}
