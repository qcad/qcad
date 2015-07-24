#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qimagereader.h>
#include <QColor>
#include <QImage>
#include <QRect>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qimage.h>
#include <qimagereader.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qrect.h>
#include <qsize.h>
#include <qstringlist.h>

static const char * const qtscript_QImageReader_function_names[] = {
    "QImageReader"
    // static
    , "imageFormat"
    , "supportedImageFormats"
    , "supportedMimeTypes"
    // prototype
    , "autoDetectImageFormat"
    , "backgroundColor"
    , "canRead"
    , "clipRect"
    , "currentImageNumber"
    , "currentImageRect"
    , "decideFormatFromContent"
    , "device"
    , "error"
    , "errorString"
    , "fileName"
    , "format"
    , "imageCount"
    , "imageFormat"
    , "jumpToImage"
    , "jumpToNextImage"
    , "loopCount"
    , "nextImageDelay"
    , "quality"
    , "read"
    , "scaledClipRect"
    , "scaledSize"
    , "setAutoDetectImageFormat"
    , "setBackgroundColor"
    , "setClipRect"
    , "setDecideFormatFromContent"
    , "setDevice"
    , "setFileName"
    , "setFormat"
    , "setQuality"
    , "setScaledClipRect"
    , "setScaledSize"
    , "size"
    , "supportsAnimation"
    , "supportsOption"
    , "text"
    , "textKeys"
    , "toString"
};

static const char * const qtscript_QImageReader_function_signatures[] = {
    "\nQIODevice device, QByteArray format\nString fileName, QByteArray format"
    // static
    , "QIODevice device\nString fileName"
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
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int imageNumber"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "bool enabled"
    , "QColor color"
    , "QRect rect"
    , "bool ignored"
    , "QIODevice device"
    , "String fileName"
    , "QByteArray format"
    , "int quality"
    , "QRect rect"
    , "QSize size"
    , ""
    , ""
    , "ImageOption option"
    , "String key"
    , ""
""
};

static const int qtscript_QImageReader_function_lengths[] = {
    2
    // static
    , 1
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
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
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
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QImageReader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QImageReader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QImageReader*)
Q_DECLARE_METATYPE(QImageReader::ImageReaderError)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QImage::Format)
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
// QImageReader::ImageReaderError
//

static const QImageReader::ImageReaderError qtscript_QImageReader_ImageReaderError_values[] = {
    QImageReader::UnknownError
    , QImageReader::FileNotFoundError
    , QImageReader::DeviceError
    , QImageReader::UnsupportedFormatError
    , QImageReader::InvalidDataError
};

static const char * const qtscript_QImageReader_ImageReaderError_keys[] = {
    "UnknownError"
    , "FileNotFoundError"
    , "DeviceError"
    , "UnsupportedFormatError"
    , "InvalidDataError"
};

static QString qtscript_QImageReader_ImageReaderError_toStringHelper(QImageReader::ImageReaderError value)
{
    if ((value >= QImageReader::UnknownError) && (value <= QImageReader::InvalidDataError))
        return qtscript_QImageReader_ImageReaderError_keys[static_cast<int>(value)-static_cast<int>(QImageReader::UnknownError)];
    return QString();
}

static QScriptValue qtscript_QImageReader_ImageReaderError_toScriptValue(QScriptEngine *engine, const QImageReader::ImageReaderError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QImageReader"));
    return clazz.property(qtscript_QImageReader_ImageReaderError_toStringHelper(value));
}

static void qtscript_QImageReader_ImageReaderError_fromScriptValue(const QScriptValue &value, QImageReader::ImageReaderError &out)
{
    out = qvariant_cast<QImageReader::ImageReaderError>(value.toVariant());
}

static QScriptValue qtscript_construct_QImageReader_ImageReaderError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QImageReader::UnknownError) && (arg <= QImageReader::InvalidDataError))
        return qScriptValueFromValue(engine,  static_cast<QImageReader::ImageReaderError>(arg));
    return context->throwError(QString::fromLatin1("ImageReaderError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QImageReader_ImageReaderError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QImageReader::ImageReaderError value = qscriptvalue_cast<QImageReader::ImageReaderError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QImageReader_ImageReaderError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QImageReader::ImageReaderError value = qscriptvalue_cast<QImageReader::ImageReaderError>(context->thisObject());
    return QScriptValue(engine, qtscript_QImageReader_ImageReaderError_toStringHelper(value));
}

static QScriptValue qtscript_create_QImageReader_ImageReaderError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QImageReader_ImageReaderError,
        qtscript_QImageReader_ImageReaderError_valueOf, qtscript_QImageReader_ImageReaderError_toString);
    qScriptRegisterMetaType<QImageReader::ImageReaderError>(engine, qtscript_QImageReader_ImageReaderError_toScriptValue,
        qtscript_QImageReader_ImageReaderError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QImageReader_ImageReaderError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QImageReader_ImageReaderError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QImageReader
//

static QScriptValue qtscript_QImageReader_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 37;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QImageReader* _q_self = qscriptvalue_cast<QImageReader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QImageReader.%0(): this object is not a QImageReader")
            .arg(qtscript_QImageReader_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->autoDetectImageFormat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->backgroundColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canRead();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->clipRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentImageNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->currentImageRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->decideFormatFromContent();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QImageReader::ImageReaderError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->imageCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QImage::Format _q_result = _q_self->imageFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->jumpToImage(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->jumpToNextImage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loopCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->nextImageDelay();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->quality();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->read();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->scaledClipRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->scaledSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAutoDetectImageFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->setBackgroundColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->setClipRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setDecideFormatFromContent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setQuality(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->setScaledClipRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        _q_self->setScaledSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->supportsAnimation();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QImageIOHandler::ImageOption _q_arg0 = qscriptvalue_cast<QImageIOHandler::ImageOption>(context->argument(0));
        bool _q_result = _q_self->supportsOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->text(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->textKeys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 37: {
    QString result = QString::fromLatin1("QImageReader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageReader_throw_ambiguity_error_helper(context,
        qtscript_QImageReader_function_names[_id+4],
        qtscript_QImageReader_function_signatures[_id+4]);
}

static QScriptValue qtscript_QImageReader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QImageReader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QImageReader* _q_cpp_result = new QImageReader();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QImageReader* _q_cpp_result = new QImageReader(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QImageReader* _q_cpp_result = new QImageReader(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QImageReader* _q_cpp_result = new QImageReader(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QImageReader* _q_cpp_result = new QImageReader(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QByteArray _q_result = QImageReader::imageFormat(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_result = QImageReader::imageFormat(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = QImageReader::supportedImageFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = QImageReader::supportedMimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageReader_throw_ambiguity_error_helper(context,
        qtscript_QImageReader_function_names[_id],
        qtscript_QImageReader_function_signatures[_id]);
}

QScriptValue qtscript_create_QImageReader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QImageReader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QImageReader*)0));
    for (int i = 0; i < 38; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImageReader_prototype_call, qtscript_QImageReader_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QImageReader_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QImageReader*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QImageReader_static_call, proto, qtscript_QImageReader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImageReader_static_call,
            qtscript_QImageReader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QImageReader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ImageReaderError"),
        qtscript_create_QImageReader_ImageReaderError_class(engine, ctor));
    return ctor;
}
