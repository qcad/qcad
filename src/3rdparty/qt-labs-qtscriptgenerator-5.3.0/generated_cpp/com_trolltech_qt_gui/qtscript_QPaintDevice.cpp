#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qpaintdevice.h>
#include <QVariant>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpoint.h>

#include "qtscriptshell_QPaintDevice.h"

static const char * const qtscript_QPaintDevice_function_names[] = {
    "QPaintDevice"
    // static
    // prototype
    , "colorCount"
    , "depth"
    , "devType"
    , "devicePixelRatio"
    , "height"
    , "heightMM"
    , "logicalDpiX"
    , "logicalDpiY"
    , "paintEngine"
    , "paintingActive"
    , "physicalDpiX"
    , "physicalDpiY"
    , "width"
    , "widthMM"
    , "toString"
};

static const char * const qtscript_QPaintDevice_function_signatures[] = {
    ""
    // static
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
""
};

static const int qtscript_QPaintDevice_function_lengths[] = {
    0
    // static
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
    , 0
};

static QScriptValue qtscript_QPaintDevice_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPaintDevice::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QtScriptShell_QPaintDevice*)
Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPaintEngine*)

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
// QPaintDevice::PaintDeviceMetric
//

static const QPaintDevice::PaintDeviceMetric qtscript_QPaintDevice_PaintDeviceMetric_values[] = {
    QPaintDevice::PdmWidth
    , QPaintDevice::PdmHeight
    , QPaintDevice::PdmWidthMM
    , QPaintDevice::PdmHeightMM
    , QPaintDevice::PdmNumColors
    , QPaintDevice::PdmDepth
    , QPaintDevice::PdmDpiX
    , QPaintDevice::PdmDpiY
    , QPaintDevice::PdmPhysicalDpiX
    , QPaintDevice::PdmPhysicalDpiY
    , QPaintDevice::PdmDevicePixelRatio
};

static const char * const qtscript_QPaintDevice_PaintDeviceMetric_keys[] = {
    "PdmWidth"
    , "PdmHeight"
    , "PdmWidthMM"
    , "PdmHeightMM"
    , "PdmNumColors"
    , "PdmDepth"
    , "PdmDpiX"
    , "PdmDpiY"
    , "PdmPhysicalDpiX"
    , "PdmPhysicalDpiY"
    , "PdmDevicePixelRatio"
};

static QString qtscript_QPaintDevice_PaintDeviceMetric_toStringHelper(QPaintDevice::PaintDeviceMetric value)
{
    if ((value >= QPaintDevice::PdmWidth) && (value <= QPaintDevice::PdmDevicePixelRatio))
        return qtscript_QPaintDevice_PaintDeviceMetric_keys[static_cast<int>(value)-static_cast<int>(QPaintDevice::PdmWidth)];
    return QString();
}

static QScriptValue qtscript_QPaintDevice_PaintDeviceMetric_toScriptValue(QScriptEngine *engine, const QPaintDevice::PaintDeviceMetric &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPaintDevice"));
    return clazz.property(qtscript_QPaintDevice_PaintDeviceMetric_toStringHelper(value));
}

static void qtscript_QPaintDevice_PaintDeviceMetric_fromScriptValue(const QScriptValue &value, QPaintDevice::PaintDeviceMetric &out)
{
    out = qvariant_cast<QPaintDevice::PaintDeviceMetric>(value.toVariant());
}

static QScriptValue qtscript_construct_QPaintDevice_PaintDeviceMetric(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPaintDevice::PdmWidth) && (arg <= QPaintDevice::PdmDevicePixelRatio))
        return qScriptValueFromValue(engine,  static_cast<QPaintDevice::PaintDeviceMetric>(arg));
    return context->throwError(QString::fromLatin1("PaintDeviceMetric(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPaintDevice_PaintDeviceMetric_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPaintDevice::PaintDeviceMetric value = qscriptvalue_cast<QPaintDevice::PaintDeviceMetric>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPaintDevice_PaintDeviceMetric_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPaintDevice::PaintDeviceMetric value = qscriptvalue_cast<QPaintDevice::PaintDeviceMetric>(context->thisObject());
    return QScriptValue(engine, qtscript_QPaintDevice_PaintDeviceMetric_toStringHelper(value));
}

static QScriptValue qtscript_create_QPaintDevice_PaintDeviceMetric_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPaintDevice_PaintDeviceMetric,
        qtscript_QPaintDevice_PaintDeviceMetric_valueOf, qtscript_QPaintDevice_PaintDeviceMetric_toString);
    qScriptRegisterMetaType<QPaintDevice::PaintDeviceMetric>(engine, qtscript_QPaintDevice_PaintDeviceMetric_toScriptValue,
        qtscript_QPaintDevice_PaintDeviceMetric_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPaintDevice_PaintDeviceMetric_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPaintDevice_PaintDeviceMetric_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPaintDevice
//

static QScriptValue qtscript_QPaintDevice_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPaintDevice* _q_self = qscriptvalue_cast<QPaintDevice*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPaintDevice.%0(): this object is not a QPaintDevice")
            .arg(qtscript_QPaintDevice_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->colorCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->depth();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->devType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->devicePixelRatio();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->height();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->heightMM();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->logicalDpiX();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->logicalDpiY();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QPaintEngine* _q_result = _q_self->paintEngine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->paintingActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->physicalDpiX();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->physicalDpiY();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->width();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->widthMM();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QPaintDevice");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPaintDevice_throw_ambiguity_error_helper(context,
        qtscript_QPaintDevice_function_names[_id+1],
        qtscript_QPaintDevice_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPaintDevice_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QPaintDevice cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPaintDevice_throw_ambiguity_error_helper(context,
        qtscript_QPaintDevice_function_names[_id],
        qtscript_QPaintDevice_function_signatures[_id]);
}

QScriptValue qtscript_create_QPaintDevice_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPaintDevice*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPaintDevice*)0));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPaintDevice_prototype_call, qtscript_QPaintDevice_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPaintDevice_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPaintDevice*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPaintDevice_static_call, proto, qtscript_QPaintDevice_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PaintDeviceMetric"),
        qtscript_create_QPaintDevice_PaintDeviceMetric_class(engine, ctor));
    return ctor;
}
