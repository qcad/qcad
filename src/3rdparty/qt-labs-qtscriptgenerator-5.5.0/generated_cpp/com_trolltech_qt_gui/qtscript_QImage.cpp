#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qimage.h>
#include <QMatrix>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qimage.h>
#include <qiodevice.h>
#include <qmatrix.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qtransform.h>
#include <qvector.h>

#include "qtscriptshell_QImage.h"

static const char * const qtscript_QImage_function_names[] = {
    "QImage"
    // static
    , "fromData"
    , "trueMatrix"
    // prototype
    , "allGray"
    , "alphaChannel"
    , "bitPlaneCount"
    , "byteCount"
    , "bytesPerLine"
    , "cacheKey"
    , "color"
    , "colorTable"
    , "constBits"
    , "constScanLine"
    , "convertToFormat"
    , "copy"
    , "createAlphaMask"
    , "createHeuristicMask"
    , "createMaskFromColor"
    , "dotsPerMeterX"
    , "dotsPerMeterY"
    , "fill"
    , "format"
    , "hasAlphaChannel"
    , "invertPixels"
    , "isGrayscale"
    , "isNull"
    , "load"
    , "loadFromData"
    , "mirrored"
    , "offset"
    , "equals"
    , "pixel"
    , "pixelIndex"
    , "rect"
    , "rgbSwapped"
    , "save"
    , "scaled"
    , "scaledToHeight"
    , "scaledToWidth"
    , "setAlphaChannel"
    , "setColor"
    , "setColorCount"
    , "setDevicePixelRatio"
    , "setDotsPerMeterX"
    , "setDotsPerMeterY"
    , "setOffset"
    , "setPixel"
    , "setText"
    , "size"
    , "swap"
    , "text"
    , "textKeys"
    , "transformed"
    , "valid"
    , "toString"
};

static const char * const qtscript_QImage_function_signatures[] = {
    "\nQImage arg__1\nQSize size, Format format\nString fileName, char format\nint width, int height, Format format"
    // static
    , "QByteArray data, char format"
    , "QMatrix arg__1, int w, int h\nQTransform arg__1, int w, int h"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int i"
    , ""
    , ""
    , "int arg__1"
    , "Format f, ImageConversionFlags flags\nFormat f, List colorTable, ImageConversionFlags flags"
    , "QRect rect\nint x, int y, int w, int h"
    , "ImageConversionFlags flags"
    , "bool clipTight"
    , "unsigned int color, MaskMode mode"
    , ""
    , ""
    , "GlobalColor color\nQColor color\nuint pixel"
    , ""
    , ""
    , "InvertMode arg__1"
    , ""
    , ""
    , "QIODevice device, char format\nString fileName, char format"
    , "QByteArray data, char aformat"
    , "bool horizontally, bool vertically"
    , ""
    , "QImage arg__1"
    , "QPoint pt\nint x, int y"
    , "QPoint pt\nint x, int y"
    , ""
    , ""
    , "QIODevice device, char format, int quality\nString fileName, char format, int quality"
    , "QSize s, AspectRatioMode aspectMode, TransformationMode mode\nint w, int h, AspectRatioMode aspectMode, TransformationMode mode"
    , "int h, TransformationMode mode"
    , "int w, TransformationMode mode"
    , "QImage alphaChannel"
    , "int i, unsigned int c"
    , "int arg__1"
    , "qreal scaleFactor"
    , "int arg__1"
    , "int arg__1"
    , "QPoint arg__1"
    , "QPoint pt, uint index_or_rgb\nint x, int y, uint index_or_rgb"
    , "String key, String value"
    , ""
    , "QImage other"
    , "String key"
    , ""
    , "QMatrix matrix, TransformationMode mode\nQTransform matrix, TransformationMode mode"
    , "QPoint pt\nint x, int y"
""
};

static const int qtscript_QImage_function_lengths[] = {
    3
    // static
    , 2
    , 3
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
    , 1
    , 3
    , 4
    , 1
    , 1
    , 2
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
    , 2
    , 0
    , 1
    , 2
    , 2
    , 0
    , 0
    , 3
    , 4
    , 2
    , 2
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 3
    , 2
    , 0
    , 1
    , 1
    , 0
    , 2
    , 2
    , 0
};

static QScriptValue qtscript_QImage_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QImage::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QImage*)
Q_DECLARE_METATYPE(QtScriptShell_QImage)
Q_DECLARE_METATYPE(QtScriptShell_QImage*)
Q_DECLARE_METATYPE(QImage::InvertMode)
Q_DECLARE_METATYPE(QImage::Format)
Q_DECLARE_METATYPE(QVector<unsigned int >)
Q_DECLARE_METATYPE(const uchar*)
Q_DECLARE_METATYPE(QFlags<Qt::ImageConversionFlag>)
Q_DECLARE_METATYPE(Qt::MaskMode)
Q_DECLARE_METATYPE(Qt::GlobalColor)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(Qt::AspectRatioMode)
Q_DECLARE_METATYPE(Qt::TransformationMode)
Q_DECLARE_METATYPE(QPaintDevice*)

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
// QImage::InvertMode
//

static const QImage::InvertMode qtscript_QImage_InvertMode_values[] = {
    QImage::InvertRgb
    , QImage::InvertRgba
};

static const char * const qtscript_QImage_InvertMode_keys[] = {
    "InvertRgb"
    , "InvertRgba"
};

static QString qtscript_QImage_InvertMode_toStringHelper(QImage::InvertMode value)
{
    if ((value >= QImage::InvertRgb) && (value <= QImage::InvertRgba))
        return qtscript_QImage_InvertMode_keys[static_cast<int>(value)-static_cast<int>(QImage::InvertRgb)];
    return QString();
}

static QScriptValue qtscript_QImage_InvertMode_toScriptValue(QScriptEngine *engine, const QImage::InvertMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QImage"));
    return clazz.property(qtscript_QImage_InvertMode_toStringHelper(value));
}

static void qtscript_QImage_InvertMode_fromScriptValue(const QScriptValue &value, QImage::InvertMode &out)
{
    out = qvariant_cast<QImage::InvertMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QImage_InvertMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QImage::InvertRgb) && (arg <= QImage::InvertRgba))
        return qScriptValueFromValue(engine,  static_cast<QImage::InvertMode>(arg));
    return context->throwError(QString::fromLatin1("InvertMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QImage_InvertMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QImage::InvertMode value = qscriptvalue_cast<QImage::InvertMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QImage_InvertMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QImage::InvertMode value = qscriptvalue_cast<QImage::InvertMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QImage_InvertMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QImage_InvertMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QImage_InvertMode,
        qtscript_QImage_InvertMode_valueOf, qtscript_QImage_InvertMode_toString);
    qScriptRegisterMetaType<QImage::InvertMode>(engine, qtscript_QImage_InvertMode_toScriptValue,
        qtscript_QImage_InvertMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QImage_InvertMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QImage_InvertMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QImage::Format
//

static const QImage::Format qtscript_QImage_Format_values[] = {
    QImage::Format_Invalid
    , QImage::Format_Mono
    , QImage::Format_MonoLSB
    , QImage::Format_Indexed8
    , QImage::Format_RGB32
    , QImage::Format_ARGB32
    , QImage::Format_ARGB32_Premultiplied
    , QImage::Format_RGB16
    , QImage::Format_ARGB8565_Premultiplied
    , QImage::Format_RGB666
    , QImage::Format_ARGB6666_Premultiplied
    , QImage::Format_RGB555
    , QImage::Format_ARGB8555_Premultiplied
    , QImage::Format_RGB888
    , QImage::Format_RGB444
    , QImage::Format_ARGB4444_Premultiplied
    , QImage::Format_RGBX8888
    , QImage::Format_RGBA8888
    , QImage::Format_RGBA8888_Premultiplied
    , QImage::Format_Grayscale8
    , QImage::NImageFormats
};

static const char * const qtscript_QImage_Format_keys[] = {
    "Format_Invalid"
    , "Format_Mono"
    , "Format_MonoLSB"
    , "Format_Indexed8"
    , "Format_RGB32"
    , "Format_ARGB32"
    , "Format_ARGB32_Premultiplied"
    , "Format_RGB16"
    , "Format_ARGB8565_Premultiplied"
    , "Format_RGB666"
    , "Format_ARGB6666_Premultiplied"
    , "Format_RGB555"
    , "Format_ARGB8555_Premultiplied"
    , "Format_RGB888"
    , "Format_RGB444"
    , "Format_ARGB4444_Premultiplied"
    , "Format_RGBX8888"
    , "Format_RGBA8888"
    , "Format_RGBA8888_Premultiplied"
    , "Format_Grayscale8"
    , "NImageFormats"
};

static QString qtscript_QImage_Format_toStringHelper(QImage::Format value)
{
    if ((value >= QImage::Format_Invalid) && (value <= QImage::NImageFormats))
        return qtscript_QImage_Format_keys[static_cast<int>(value)-static_cast<int>(QImage::Format_Invalid)];
    return QString();
}

static QScriptValue qtscript_QImage_Format_toScriptValue(QScriptEngine *engine, const QImage::Format &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QImage"));
    return clazz.property(qtscript_QImage_Format_toStringHelper(value));
}

static void qtscript_QImage_Format_fromScriptValue(const QScriptValue &value, QImage::Format &out)
{
    out = qvariant_cast<QImage::Format>(value.toVariant());
}

static QScriptValue qtscript_construct_QImage_Format(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QImage::Format_Invalid) && (arg <= QImage::NImageFormats))
        return qScriptValueFromValue(engine,  static_cast<QImage::Format>(arg));
    return context->throwError(QString::fromLatin1("Format(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QImage_Format_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QImage::Format value = qscriptvalue_cast<QImage::Format>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QImage_Format_toString(QScriptContext *context, QScriptEngine *engine)
{
    QImage::Format value = qscriptvalue_cast<QImage::Format>(context->thisObject());
    return QScriptValue(engine, qtscript_QImage_Format_toStringHelper(value));
}

static QScriptValue qtscript_create_QImage_Format_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QImage_Format,
        qtscript_QImage_Format_valueOf, qtscript_QImage_Format_toString);
    qScriptRegisterMetaType<QImage::Format>(engine, qtscript_QImage_Format_toScriptValue,
        qtscript_QImage_Format_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 20; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QImage_Format_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QImage_Format_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QImage
//

static QScriptValue qtscript_QImage_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 51;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QImage* _q_self = qscriptvalue_cast<QImage*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QImage.%0(): this object is not a QImage")
            .arg(qtscript_QImage_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->allGray();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->alphaChannel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->bitPlaneCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->byteCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->bytesPerLine();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->cacheKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        unsigned int _q_result = _q_self->color(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QVector<unsigned int > _q_result = _q_self->colorTable();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        const uchar* _q_result = const_cast<const uchar*>(_q_self->constBits());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        const uchar* _q_result = const_cast<const uchar*>(_q_self->constScanLine(_q_arg0));
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QImage::Format _q_arg0 = qscriptvalue_cast<QImage::Format>(context->argument(0));
        QImage _q_result = _q_self->convertToFormat(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QImage::Format>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::ImageConversionFlag> >() == context->argument(1).toVariant().userType())) {
            QImage::Format _q_arg0 = qscriptvalue_cast<QImage::Format>(context->argument(0));
            QFlags<Qt::ImageConversionFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(1));
            QImage _q_result = _q_self->convertToFormat(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QImage::Format>() == context->argument(0).toVariant().userType())
            && context->argument(1).isArray()) {
            QImage::Format _q_arg0 = qscriptvalue_cast<QImage::Format>(context->argument(0));
            QVector<uint> _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            QImage _q_result = _q_self->convertToFormat(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QImage::Format _q_arg0 = qscriptvalue_cast<QImage::Format>(context->argument(0));
        QVector<uint> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        QFlags<Qt::ImageConversionFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(2));
        QImage _q_result = _q_self->convertToFormat(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->copy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QImage _q_result = _q_self->copy(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QImage _q_result = _q_self->copy(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->createAlphaMask();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<Qt::ImageConversionFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(0));
        QImage _q_result = _q_self->createAlphaMask(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->createHeuristicMask();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QImage _q_result = _q_self->createHeuristicMask(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        QImage _q_result = _q_self->createMaskFromColor(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        uint _q_arg0 = context->argument(0).toUInt32();
        Qt::MaskMode _q_arg1 = qscriptvalue_cast<Qt::MaskMode>(context->argument(1));
        QImage _q_result = _q_self->createMaskFromColor(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->dotsPerMeterX();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->dotsPerMeterY();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::GlobalColor>() == context->argument(0).toVariant().userType())) {
            Qt::GlobalColor _q_arg0 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(0));
            _q_self->fill(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            _q_self->fill(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()) {
            uint _q_arg0 = context->argument(0).toUInt32();
            _q_self->fill(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QImage::Format _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasAlphaChannel();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        _q_self->invertPixels();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QImage::InvertMode _q_arg0 = qscriptvalue_cast<QImage::InvertMode>(context->argument(0));
        _q_self->invertPixels(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isGrayscale();
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
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    bool _q_result = _q_self->load(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    bool _q_result = _q_self->load(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                bool _q_result = _q_self->loadFromData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->mirrored();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QImage _q_result = _q_self->mirrored(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        bool _q_arg0 = context->argument(0).toBoolean();
        bool _q_arg1 = context->argument(1).toBoolean();
        QImage _q_result = _q_self->mirrored(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->offset();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        unsigned int _q_result = _q_self->pixel(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        unsigned int _q_result = _q_self->pixel(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_result = _q_self->pixelIndex(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->pixelIndex(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->rect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->rgbSwapped();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_result = _q_self->save(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->save(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    bool _q_result = _q_self->save(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    bool _q_result = _q_self->save(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isNumber()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    int _q_arg2 = context->argument(2).toInt32();
            bool _q_result = _q_self->save(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    int _q_arg2 = context->argument(2).toInt32();
            bool _q_result = _q_self->save(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QImage _q_result = _q_self->scaled(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(1).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
            QImage _q_result = _q_self->scaled(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QImage _q_result = _q_self->scaled(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<Qt::TransformationMode>() == context->argument(2).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
            Qt::TransformationMode _q_arg2 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(2));
            QImage _q_result = _q_self->scaled(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            Qt::AspectRatioMode _q_arg2 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(2));
            QImage _q_result = _q_self->scaled(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        Qt::AspectRatioMode _q_arg2 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(2));
        Qt::TransformationMode _q_arg3 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(3));
        QImage _q_result = _q_self->scaled(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QImage _q_result = _q_self->scaledToHeight(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
        QImage _q_result = _q_self->scaledToHeight(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QImage _q_result = _q_self->scaledToWidth(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
        QImage _q_result = _q_self->scaledToWidth(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        _q_self->setAlphaChannel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        uint _q_arg1 = context->argument(1).toUInt32();
        _q_self->setColor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setColorCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setDevicePixelRatio(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setDotsPerMeterX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setDotsPerMeterY(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setOffset(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        uint _q_arg1 = context->argument(1).toUInt32();
        _q_self->setPixel(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        uint _q_arg2 = context->argument(2).toUInt32();
        _q_self->setPixel(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->text(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->textKeys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            QImage _q_result = _q_self->transformed(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            QImage _q_result = _q_self->transformed(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::TransformationMode>() == context->argument(1).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
            QImage _q_result = _q_self->transformed(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::TransformationMode>() == context->argument(1).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            Qt::TransformationMode _q_arg1 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(1));
            QImage _q_result = _q_self->transformed(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        bool _q_result = _q_self->valid(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->valid(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 51: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImage_throw_ambiguity_error_helper(context,
        qtscript_QImage_function_names[_id+3],
        qtscript_QImage_function_signatures[_id+3]);
}

static QScriptValue qtscript_QImage_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QImage(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QImage _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QImage)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QImage>() == context->argument(0).toVariant().userType())) {
            QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
            QtScriptShell_QImage _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QImage)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QImage _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QImage)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage::Format>() == context->argument(1).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QImage::Format _q_arg1 = qscriptvalue_cast<QImage::Format>(context->argument(1));
            QtScriptShell_QImage _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QImage)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    QtScriptShell_QImage _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QImage)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QImage::Format _q_arg2 = qscriptvalue_cast<QImage::Format>(context->argument(2));
        QtScriptShell_QImage _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QImage)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QImage _q_result = QImage::fromData(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            QMatrix _q_result = QImage::trueMatrix(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            QTransform _q_result = QImage::trueMatrix(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImage_throw_ambiguity_error_helper(context,
        qtscript_QImage_function_names[_id],
        qtscript_QImage_function_signatures[_id]);
}

QScriptValue qtscript_create_QImage_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QImage*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QImage*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QPaintDevice*>()));
    for (int i = 0; i < 52; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImage_prototype_call, qtscript_QImage_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QImage_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QImage>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QImage*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QImage_static_call, proto, qtscript_QImage_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImage_static_call,
            qtscript_QImage_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QImage_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("InvertMode"),
        qtscript_create_QImage_InvertMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Format"),
        qtscript_create_QImage_Format_class(engine, ctor));
    return ctor;
}
