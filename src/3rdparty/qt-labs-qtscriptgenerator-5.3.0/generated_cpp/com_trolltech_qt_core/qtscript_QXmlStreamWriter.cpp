#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxmlstream.h>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qtextcodec.h>
#include <qxmlstream.h>

static const char * const qtscript_QXmlStreamWriter_function_names[] = {
    "QXmlStreamWriter"
    // static
    // prototype
    , "autoFormatting"
    , "autoFormattingIndent"
    , "codec"
    , "device"
    , "hasError"
    , "setAutoFormatting"
    , "setAutoFormattingIndent"
    , "setCodec"
    , "setDevice"
    , "writeAttribute"
    , "writeAttributes"
    , "writeCDATA"
    , "writeCharacters"
    , "writeComment"
    , "writeCurrentToken"
    , "writeDTD"
    , "writeDefaultNamespace"
    , "writeEmptyElement"
    , "writeEndDocument"
    , "writeEndElement"
    , "writeEntityReference"
    , "writeNamespace"
    , "writeProcessingInstruction"
    , "writeStartDocument"
    , "writeStartElement"
    , "writeTextElement"
    , "toString"
};

static const char * const qtscript_QXmlStreamWriter_function_signatures[] = {
    "\nQByteArray array\nQIODevice device"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "bool arg__1"
    , "int spacesOrTabs"
    , "QTextCodec codec\nchar codecName"
    , "QIODevice device"
    , "String namespaceUri, String name, String value\nString qualifiedName, String value\nQXmlStreamAttribute attribute"
    , "QXmlStreamAttributes attributes"
    , "String text"
    , "String text"
    , "String text"
    , "QXmlStreamReader reader"
    , "String dtd"
    , "String namespaceUri"
    , "String namespaceUri, String name\nString qualifiedName"
    , ""
    , ""
    , "String name"
    , "String namespaceUri, String prefix"
    , "String target, String data"
    , "\nString version\nString version, bool standalone"
    , "String namespaceUri, String name\nString qualifiedName"
    , "String namespaceUri, String name, String text\nString qualifiedName, String text"
""
};

static const int qtscript_QXmlStreamWriter_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 3
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 0
    , 0
    , 1
    , 2
    , 2
    , 2
    , 2
    , 3
    , 0
};

static QScriptValue qtscript_QXmlStreamWriter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlStreamWriter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlStreamWriter*)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QXmlStreamAttribute)
Q_DECLARE_METATYPE(QXmlStreamAttributes)
Q_DECLARE_METATYPE(QXmlStreamReader*)
Q_DECLARE_METATYPE(QByteArray*)

//
// QXmlStreamWriter
//

static QScriptValue qtscript_QXmlStreamWriter_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 26;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlStreamWriter* _q_self = qscriptvalue_cast<QXmlStreamWriter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlStreamWriter.%0(): this object is not a QXmlStreamWriter")
            .arg(qtscript_QXmlStreamWriter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->autoFormatting();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->autoFormattingIndent();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTextCodec* _q_result = _q_self->codec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasError();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAutoFormatting(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setAutoFormattingIndent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QTextCodec*>(context->argument(0))) {
            QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
            _q_self->setCodec(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {

              // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                        _q_self->setCodec(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        _q_self->writeAttribute(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->writeAttribute(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        _q_self->writeAttribute(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QXmlStreamAttributes _q_arg0 = qscriptvalue_cast<QXmlStreamAttributes>(context->argument(0));
        _q_self->writeAttributes(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeCDATA(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeCharacters(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeComment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {

            QXmlStreamReader & _q_arg0 = *qscriptvalue_cast<QXmlStreamReader*>(context->argument(0));
                    _q_self->writeCurrentToken(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeDTD(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeDefaultNamespace(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeEmptyElement(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->writeEmptyElement(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        _q_self->writeEndDocument();
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        _q_self->writeEndElement();
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeEntityReference(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeNamespace(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->writeNamespace(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeProcessingInstruction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->writeProcessingInstruction(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->writeStartDocument();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeStartDocument(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->writeStartDocument(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->writeStartElement(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->writeStartElement(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->writeTextElement(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        _q_self->writeTextElement(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 26: {
    QString result = QString::fromLatin1("QXmlStreamWriter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamWriter_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamWriter_function_names[_id+1],
        qtscript_QXmlStreamWriter_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlStreamWriter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlStreamWriter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlStreamWriter* _q_cpp_result = new QXmlStreamWriter();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QByteArray*>(context->argument(0))) {
            QByteArray* _q_arg0 = qscriptvalue_cast<QByteArray*>(context->argument(0));
            QXmlStreamWriter* _q_cpp_result = new QXmlStreamWriter(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QXmlStreamWriter* _q_cpp_result = new QXmlStreamWriter(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamWriter_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamWriter_function_names[_id],
        qtscript_QXmlStreamWriter_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlStreamWriter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamWriter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlStreamWriter*)0));
    for (int i = 0; i < 27; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamWriter_prototype_call, qtscript_QXmlStreamWriter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlStreamWriter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamWriter*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlStreamWriter_static_call, proto, qtscript_QXmlStreamWriter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
