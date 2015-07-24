#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qimagewriter.h>
#include <QVariant>
#include <qbytearray.h>
#include <qimage.h>
#include <qimagewriter.h>
#include <qiodevice.h>
#include <qlist.h>

static const char * const qtscript_QImageWriter_function_names[] = {
    "QImageWriter"
    // static
    , "supportedImageFormats"
    , "supportedMimeTypes"
    // prototype
    , "canWrite"
    , "compression"
    , "device"
    , "error"
    , "errorString"
    , "fileName"
    , "format"
    , "gamma"
    , "quality"
    , "setCompression"
    , "setDevice"
    , "setFileName"
    , "setFormat"
    , "setGamma"
    , "setQuality"
    , "setText"
    , "supportsOption"
    , "write"
    , "toString"
};

static const char * const qtscript_QImageWriter_function_signatures[] = {
    "\nQIODevice device, QByteArray format\nString fileName, QByteArray format"
    // static
    , ""
    , ""
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int compression"
    , "QIODevice device"
    , "String fileName"
    , "QByteArray format"
    , "float gamma"
    , "int quality"
    , "String key, String text"
    , "ImageOption option"
    , "QImage image"
""
};

static const int qtscript_QImageWriter_function_lengths[] = {
    2
    // static
    , 0
    , 0
    // prototype
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
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QImageWriter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QImageWriter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QImageWriter*)
Q_DECLARE_METATYPE(QImageWriter::ImageWriterError)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QImageIOHandler::ImageOption)
Q_DECLARE_METATYPE(QList<QByteArray >)

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
// QImageWriter::ImageWriterError
//

static const QImageWriter::ImageWriterError qtscript_QImageWriter_ImageWriterError_values[] = {
    QImageWriter::UnknownError
    , QImageWriter::DeviceError
    , QImageWriter::UnsupportedFormatError
};

static const char * const qtscript_QImageWriter_ImageWriterError_keys[] = {
    "UnknownError"
    , "DeviceError"
    , "UnsupportedFormatError"
};

static QString qtscript_QImageWriter_ImageWriterError_toStringHelper(QImageWriter::ImageWriterError value)
{
    if ((value >= QImageWriter::UnknownError) && (value <= QImageWriter::UnsupportedFormatError))
        return qtscript_QImageWriter_ImageWriterError_keys[static_cast<int>(value)-static_cast<int>(QImageWriter::UnknownError)];
    return QString();
}

static QScriptValue qtscript_QImageWriter_ImageWriterError_toScriptValue(QScriptEngine *engine, const QImageWriter::ImageWriterError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QImageWriter"));
    return clazz.property(qtscript_QImageWriter_ImageWriterError_toStringHelper(value));
}

static void qtscript_QImageWriter_ImageWriterError_fromScriptValue(const QScriptValue &value, QImageWriter::ImageWriterError &out)
{
    out = qvariant_cast<QImageWriter::ImageWriterError>(value.toVariant());
}

static QScriptValue qtscript_construct_QImageWriter_ImageWriterError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QImageWriter::UnknownError) && (arg <= QImageWriter::UnsupportedFormatError))
        return qScriptValueFromValue(engine,  static_cast<QImageWriter::ImageWriterError>(arg));
    return context->throwError(QString::fromLatin1("ImageWriterError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QImageWriter_ImageWriterError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QImageWriter::ImageWriterError value = qscriptvalue_cast<QImageWriter::ImageWriterError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QImageWriter_ImageWriterError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QImageWriter::ImageWriterError value = qscriptvalue_cast<QImageWriter::ImageWriterError>(context->thisObject());
    return QScriptValue(engine, qtscript_QImageWriter_ImageWriterError_toStringHelper(value));
}

static QScriptValue qtscript_create_QImageWriter_ImageWriterError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QImageWriter_ImageWriterError,
        qtscript_QImageWriter_ImageWriterError_valueOf, qtscript_QImageWriter_ImageWriterError_toString);
    qScriptRegisterMetaType<QImageWriter::ImageWriterError>(engine, qtscript_QImageWriter_ImageWriterError_toScriptValue,
        qtscript_QImageWriter_ImageWriterError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QImageWriter_ImageWriterError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QImageWriter_ImageWriterError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QImageWriter
//

static QScriptValue qtscript_QImageWriter_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 18;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QImageWriter* _q_self = qscriptvalue_cast<QImageWriter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QImageWriter.%0(): this object is not a QImageWriter")
            .arg(qtscript_QImageWriter_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canWrite();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->compression();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QImageWriter::ImageWriterError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->gamma();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->quality();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setCompression(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setGamma(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setQuality(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QImageIOHandler::ImageOption _q_arg0 = qscriptvalue_cast<QImageIOHandler::ImageOption>(context->argument(0));
        bool _q_result = _q_self->supportsOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        bool _q_result = _q_self->write(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18: {
    QString result = QString::fromLatin1("QImageWriter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageWriter_throw_ambiguity_error_helper(context,
        qtscript_QImageWriter_function_names[_id+3],
        qtscript_QImageWriter_function_signatures[_id+3]);
}

static QScriptValue qtscript_QImageWriter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QImageWriter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QImageWriter* _q_cpp_result = new QImageWriter();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QImageWriter* _q_cpp_result = new QImageWriter(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QImageWriter* _q_cpp_result = new QImageWriter(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QImageWriter* _q_cpp_result = new QImageWriter(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = QImageWriter::supportedImageFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = QImageWriter::supportedMimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageWriter_throw_ambiguity_error_helper(context,
        qtscript_QImageWriter_function_names[_id],
        qtscript_QImageWriter_function_signatures[_id]);
}

QScriptValue qtscript_create_QImageWriter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QImageWriter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QImageWriter*)0));
    for (int i = 0; i < 19; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImageWriter_prototype_call, qtscript_QImageWriter_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QImageWriter_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QImageWriter*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QImageWriter_static_call, proto, qtscript_QImageWriter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImageWriter_static_call,
            qtscript_QImageWriter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QImageWriter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ImageWriterError"),
        qtscript_create_QImageWriter_ImageWriterError_class(engine, ctor));
    return ctor;
}
