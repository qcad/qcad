#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicseffect.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qgraphicseffect.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>

#include "qtscriptshell_QGraphicsEffect.h"

static const char * const qtscript_QGraphicsEffect_function_names[] = {
    "QGraphicsEffect"
    // static
    // prototype
    , "boundingRect"
    , "boundingRectFor"
    , "toString"
};

static const char * const qtscript_QGraphicsEffect_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QRectF sourceRect"
""
};

static const int qtscript_QGraphicsEffect_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsEffect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsEffect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsEffect*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsEffect*)
Q_DECLARE_METATYPE(QGraphicsEffect::PixmapPadMode)
Q_DECLARE_METATYPE(QGraphicsEffect::ChangeFlag)
Q_DECLARE_METATYPE(QFlags<QGraphicsEffect::ChangeFlag>)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QGraphicsEffect::PixmapPadMode
//

static const QGraphicsEffect::PixmapPadMode qtscript_QGraphicsEffect_PixmapPadMode_values[] = {
    QGraphicsEffect::NoPad
    , QGraphicsEffect::PadToTransparentBorder
    , QGraphicsEffect::PadToEffectiveBoundingRect
};

static const char * const qtscript_QGraphicsEffect_PixmapPadMode_keys[] = {
    "NoPad"
    , "PadToTransparentBorder"
    , "PadToEffectiveBoundingRect"
};

static QString qtscript_QGraphicsEffect_PixmapPadMode_toStringHelper(QGraphicsEffect::PixmapPadMode value)
{
    if ((value >= QGraphicsEffect::NoPad) && (value <= QGraphicsEffect::PadToEffectiveBoundingRect))
        return qtscript_QGraphicsEffect_PixmapPadMode_keys[static_cast<int>(value)-static_cast<int>(QGraphicsEffect::NoPad)];
    return QString();
}

static QScriptValue qtscript_QGraphicsEffect_PixmapPadMode_toScriptValue(QScriptEngine *engine, const QGraphicsEffect::PixmapPadMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsEffect"));
    return clazz.property(qtscript_QGraphicsEffect_PixmapPadMode_toStringHelper(value));
}

static void qtscript_QGraphicsEffect_PixmapPadMode_fromScriptValue(const QScriptValue &value, QGraphicsEffect::PixmapPadMode &out)
{
    out = qvariant_cast<QGraphicsEffect::PixmapPadMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsEffect_PixmapPadMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsEffect::NoPad) && (arg <= QGraphicsEffect::PadToEffectiveBoundingRect))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsEffect::PixmapPadMode>(arg));
    return context->throwError(QString::fromLatin1("PixmapPadMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsEffect_PixmapPadMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsEffect::PixmapPadMode value = qscriptvalue_cast<QGraphicsEffect::PixmapPadMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsEffect_PixmapPadMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsEffect::PixmapPadMode value = qscriptvalue_cast<QGraphicsEffect::PixmapPadMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsEffect_PixmapPadMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsEffect_PixmapPadMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsEffect_PixmapPadMode,
        qtscript_QGraphicsEffect_PixmapPadMode_valueOf, qtscript_QGraphicsEffect_PixmapPadMode_toString);
    qScriptRegisterMetaType<QGraphicsEffect::PixmapPadMode>(engine, qtscript_QGraphicsEffect_PixmapPadMode_toScriptValue,
        qtscript_QGraphicsEffect_PixmapPadMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsEffect_PixmapPadMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsEffect_PixmapPadMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsEffect::ChangeFlag
//

static const QGraphicsEffect::ChangeFlag qtscript_QGraphicsEffect_ChangeFlag_values[] = {
    QGraphicsEffect::SourceAttached
    , QGraphicsEffect::SourceDetached
    , QGraphicsEffect::SourceBoundingRectChanged
    , QGraphicsEffect::SourceInvalidated
};

static const char * const qtscript_QGraphicsEffect_ChangeFlag_keys[] = {
    "SourceAttached"
    , "SourceDetached"
    , "SourceBoundingRectChanged"
    , "SourceInvalidated"
};

static QString qtscript_QGraphicsEffect_ChangeFlag_toStringHelper(QGraphicsEffect::ChangeFlag value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QGraphicsEffect_ChangeFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QGraphicsEffect_ChangeFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QGraphicsEffect_ChangeFlag_toScriptValue(QScriptEngine *engine, const QGraphicsEffect::ChangeFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsEffect"));
    return clazz.property(qtscript_QGraphicsEffect_ChangeFlag_toStringHelper(value));
}

static void qtscript_QGraphicsEffect_ChangeFlag_fromScriptValue(const QScriptValue &value, QGraphicsEffect::ChangeFlag &out)
{
    out = qvariant_cast<QGraphicsEffect::ChangeFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsEffect_ChangeFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QGraphicsEffect_ChangeFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QGraphicsEffect::ChangeFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("ChangeFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsEffect_ChangeFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsEffect::ChangeFlag value = qscriptvalue_cast<QGraphicsEffect::ChangeFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsEffect_ChangeFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsEffect::ChangeFlag value = qscriptvalue_cast<QGraphicsEffect::ChangeFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsEffect_ChangeFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsEffect_ChangeFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsEffect_ChangeFlag,
        qtscript_QGraphicsEffect_ChangeFlag_valueOf, qtscript_QGraphicsEffect_ChangeFlag_toString);
    qScriptRegisterMetaType<QGraphicsEffect::ChangeFlag>(engine, qtscript_QGraphicsEffect_ChangeFlag_toScriptValue,
        qtscript_QGraphicsEffect_ChangeFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsEffect_ChangeFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsEffect_ChangeFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsEffect::ChangeFlags
//

static QScriptValue qtscript_QGraphicsEffect_ChangeFlags_toScriptValue(QScriptEngine *engine, const QGraphicsEffect::ChangeFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QGraphicsEffect_ChangeFlags_fromScriptValue(const QScriptValue &value, QGraphicsEffect::ChangeFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QGraphicsEffect::ChangeFlags>())
        out = qvariant_cast<QGraphicsEffect::ChangeFlags>(var);
    else if (var.userType() == qMetaTypeId<QGraphicsEffect::ChangeFlag>())
        out = qvariant_cast<QGraphicsEffect::ChangeFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QGraphicsEffect_ChangeFlags(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsEffect::ChangeFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QGraphicsEffect::ChangeFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QGraphicsEffect::ChangeFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ChangeFlags(): argument %0 is not of type ChangeFlag").arg(i));
            }
            result |= qvariant_cast<QGraphicsEffect::ChangeFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QGraphicsEffect_ChangeFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsEffect::ChangeFlags value = qscriptvalue_cast<QGraphicsEffect::ChangeFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsEffect_ChangeFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsEffect::ChangeFlags value = qscriptvalue_cast<QGraphicsEffect::ChangeFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QGraphicsEffect_ChangeFlag_values[i]) == qtscript_QGraphicsEffect_ChangeFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QGraphicsEffect_ChangeFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QGraphicsEffect_ChangeFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QGraphicsEffect::ChangeFlags>() == otherObj.value<QGraphicsEffect::ChangeFlags>())));
}

static QScriptValue qtscript_create_QGraphicsEffect_ChangeFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QGraphicsEffect_ChangeFlags, qtscript_QGraphicsEffect_ChangeFlags_valueOf,
        qtscript_QGraphicsEffect_ChangeFlags_toString, qtscript_QGraphicsEffect_ChangeFlags_equals);
    qScriptRegisterMetaType<QGraphicsEffect::ChangeFlags>(engine, qtscript_QGraphicsEffect_ChangeFlags_toScriptValue,
        qtscript_QGraphicsEffect_ChangeFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QGraphicsEffect
//

static QScriptValue qtscript_QGraphicsEffect_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsEffect* _q_self = qscriptvalue_cast<QGraphicsEffect*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsEffect.%0(): this object is not a QGraphicsEffect")
            .arg(qtscript_QGraphicsEffect_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->boundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QRectF _q_result = _q_self->boundingRectFor(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QGraphicsEffect");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsEffect_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsEffect_function_names[_id+1],
        qtscript_QGraphicsEffect_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsEffect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsEffect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsEffect* _q_cpp_result = new QtScriptShell_QGraphicsEffect();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QGraphicsEffect* _q_cpp_result = new QtScriptShell_QGraphicsEffect(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsEffect_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsEffect_function_names[_id],
        qtscript_QGraphicsEffect_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsEffect_toScriptValue(QScriptEngine *engine, QGraphicsEffect* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsEffect_fromScriptValue(const QScriptValue &value, QGraphicsEffect* &out)
{
    out = qobject_cast<QGraphicsEffect*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsEffect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsEffect*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsEffect*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsEffect_prototype_call, qtscript_QGraphicsEffect_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsEffect_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsEffect*>(engine, qtscript_QGraphicsEffect_toScriptValue, 
        qtscript_QGraphicsEffect_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsEffect_static_call, proto, qtscript_QGraphicsEffect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PixmapPadMode"),
        qtscript_create_QGraphicsEffect_PixmapPadMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ChangeFlag"),
        qtscript_create_QGraphicsEffect_ChangeFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ChangeFlags"),
        qtscript_create_QGraphicsEffect_ChangeFlags_class(engine));
    return ctor;
}
