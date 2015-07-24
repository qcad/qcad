#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qimageiohandler.h>
#include <QRect>
#include <QVariant>
#include <qbytearray.h>
#include <qimage.h>
#include <qimageiohandler.h>
#include <qiodevice.h>
#include <qrect.h>

#include "qtscriptshell_QImageIOHandler.h"

static const char * const qtscript_QImageIOHandler_function_names[] = {
    "QImageIOHandler"
    // static
    // prototype
    , "canRead"
    , "currentImageNumber"
    , "currentImageRect"
    , "device"
    , "format"
    , "imageCount"
    , "jumpToImage"
    , "jumpToNextImage"
    , "loopCount"
    , "nextImageDelay"
    , "option"
    , "read"
    , "setDevice"
    , "setFormat"
    , "setOption"
    , "supportsOption"
    , "write"
    , "toString"
};

static const char * const qtscript_QImageIOHandler_function_signatures[] = {
    ""
    // static
    // prototype
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
    , "ImageOption option"
    , "QImage image"
    , "QIODevice device"
    , "QByteArray format"
    , "ImageOption option, Object value"
    , "ImageOption option"
    , "QImage image"
""
};

static const int qtscript_QImageIOHandler_function_lengths[] = {
    0
    // static
    // prototype
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
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QImageIOHandler_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QImageIOHandler::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QImageIOHandler*)
Q_DECLARE_METATYPE(QtScriptShell_QImageIOHandler*)
Q_DECLARE_METATYPE(QImageIOHandler::ImageOption)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QImage*)

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
// QImageIOHandler::ImageOption
//

static const QImageIOHandler::ImageOption qtscript_QImageIOHandler_ImageOption_values[] = {
    QImageIOHandler::Size
    , QImageIOHandler::ClipRect
    , QImageIOHandler::Description
    , QImageIOHandler::ScaledClipRect
    , QImageIOHandler::ScaledSize
    , QImageIOHandler::CompressionRatio
    , QImageIOHandler::Gamma
    , QImageIOHandler::Quality
    , QImageIOHandler::Name
    , QImageIOHandler::SubType
    , QImageIOHandler::IncrementalReading
    , QImageIOHandler::Endianness
    , QImageIOHandler::Animation
    , QImageIOHandler::BackgroundColor
    , QImageIOHandler::ImageFormat
};

static const char * const qtscript_QImageIOHandler_ImageOption_keys[] = {
    "Size"
    , "ClipRect"
    , "Description"
    , "ScaledClipRect"
    , "ScaledSize"
    , "CompressionRatio"
    , "Gamma"
    , "Quality"
    , "Name"
    , "SubType"
    , "IncrementalReading"
    , "Endianness"
    , "Animation"
    , "BackgroundColor"
    , "ImageFormat"
};

static QString qtscript_QImageIOHandler_ImageOption_toStringHelper(QImageIOHandler::ImageOption value)
{
    if ((value >= QImageIOHandler::Size) && (value <= QImageIOHandler::ImageFormat))
        return qtscript_QImageIOHandler_ImageOption_keys[static_cast<int>(value)-static_cast<int>(QImageIOHandler::Size)];
    return QString();
}

static QScriptValue qtscript_QImageIOHandler_ImageOption_toScriptValue(QScriptEngine *engine, const QImageIOHandler::ImageOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QImageIOHandler"));
    return clazz.property(qtscript_QImageIOHandler_ImageOption_toStringHelper(value));
}

static void qtscript_QImageIOHandler_ImageOption_fromScriptValue(const QScriptValue &value, QImageIOHandler::ImageOption &out)
{
    out = qvariant_cast<QImageIOHandler::ImageOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QImageIOHandler_ImageOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QImageIOHandler::Size) && (arg <= QImageIOHandler::ImageFormat))
        return qScriptValueFromValue(engine,  static_cast<QImageIOHandler::ImageOption>(arg));
    return context->throwError(QString::fromLatin1("ImageOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QImageIOHandler_ImageOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QImageIOHandler::ImageOption value = qscriptvalue_cast<QImageIOHandler::ImageOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QImageIOHandler_ImageOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QImageIOHandler::ImageOption value = qscriptvalue_cast<QImageIOHandler::ImageOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QImageIOHandler_ImageOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QImageIOHandler_ImageOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QImageIOHandler_ImageOption,
        qtscript_QImageIOHandler_ImageOption_valueOf, qtscript_QImageIOHandler_ImageOption_toString);
    qScriptRegisterMetaType<QImageIOHandler::ImageOption>(engine, qtscript_QImageIOHandler_ImageOption_toScriptValue,
        qtscript_QImageIOHandler_ImageOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QImageIOHandler_ImageOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QImageIOHandler_ImageOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QImageIOHandler
//

static QScriptValue qtscript_QImageIOHandler_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QImageIOHandler* _q_self = qscriptvalue_cast<QImageIOHandler*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QImageIOHandler.%0(): this object is not a QImageIOHandler")
            .arg(qtscript_QImageIOHandler_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canRead();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentImageNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->currentImageRect();
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
        QByteArray _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->imageCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->jumpToImage(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->jumpToNextImage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loopCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->nextImageDelay();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QImageIOHandler::ImageOption _q_arg0 = qscriptvalue_cast<QImageIOHandler::ImageOption>(context->argument(0));
        QVariant _q_result = _q_self->option(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QImage* _q_arg0 = qscriptvalue_cast<QImage*>(context->argument(0));
        bool _q_result = _q_self->read(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        QImageIOHandler::ImageOption _q_arg0 = qscriptvalue_cast<QImageIOHandler::ImageOption>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QImageIOHandler::ImageOption _q_arg0 = qscriptvalue_cast<QImageIOHandler::ImageOption>(context->argument(0));
        bool _q_result = _q_self->supportsOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        bool _q_result = _q_self->write(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("QImageIOHandler");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageIOHandler_throw_ambiguity_error_helper(context,
        qtscript_QImageIOHandler_function_names[_id+1],
        qtscript_QImageIOHandler_function_signatures[_id+1]);
}

static QScriptValue qtscript_QImageIOHandler_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QImageIOHandler(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QImageIOHandler* _q_cpp_result = new QtScriptShell_QImageIOHandler();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QImageIOHandler*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageIOHandler_throw_ambiguity_error_helper(context,
        qtscript_QImageIOHandler_function_names[_id],
        qtscript_QImageIOHandler_function_signatures[_id]);
}

QScriptValue qtscript_create_QImageIOHandler_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QImageIOHandler*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QImageIOHandler*)0));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImageIOHandler_prototype_call, qtscript_QImageIOHandler_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QImageIOHandler_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QImageIOHandler*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QImageIOHandler_static_call, proto, qtscript_QImageIOHandler_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ImageOption"),
        qtscript_create_QImageIOHandler_ImageOption_class(engine, ctor));
    return ctor;
}
