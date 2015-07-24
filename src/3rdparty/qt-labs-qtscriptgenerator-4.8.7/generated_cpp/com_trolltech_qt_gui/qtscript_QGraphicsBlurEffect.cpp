#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

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

#include "qtscriptshell_QGraphicsBlurEffect.h"

static const char * const qtscript_QGraphicsBlurEffect_function_names[] = {
    "QGraphicsBlurEffect"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QGraphicsBlurEffect_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QGraphicsBlurEffect_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QGraphicsBlurEffect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsBlurEffect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsBlurEffect*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsBlurEffect*)
Q_DECLARE_METATYPE(QGraphicsBlurEffect::BlurHint)
Q_DECLARE_METATYPE(QFlags<QGraphicsBlurEffect::BlurHint>)
Q_DECLARE_METATYPE(QGraphicsEffect*)

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
// QGraphicsBlurEffect::BlurHint
//

static const QGraphicsBlurEffect::BlurHint qtscript_QGraphicsBlurEffect_BlurHint_values[] = {
    QGraphicsBlurEffect::PerformanceHint
    , QGraphicsBlurEffect::QualityHint
    , QGraphicsBlurEffect::AnimationHint
};

static const char * const qtscript_QGraphicsBlurEffect_BlurHint_keys[] = {
    "PerformanceHint"
    , "QualityHint"
    , "AnimationHint"
};

static QString qtscript_QGraphicsBlurEffect_BlurHint_toStringHelper(QGraphicsBlurEffect::BlurHint value)
{
    if ((value >= QGraphicsBlurEffect::PerformanceHint) && (value <= QGraphicsBlurEffect::AnimationHint))
        return qtscript_QGraphicsBlurEffect_BlurHint_keys[static_cast<int>(value)-static_cast<int>(QGraphicsBlurEffect::PerformanceHint)];
    return QString();
}

static QScriptValue qtscript_QGraphicsBlurEffect_BlurHint_toScriptValue(QScriptEngine *engine, const QGraphicsBlurEffect::BlurHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsBlurEffect"));
    return clazz.property(qtscript_QGraphicsBlurEffect_BlurHint_toStringHelper(value));
}

static void qtscript_QGraphicsBlurEffect_BlurHint_fromScriptValue(const QScriptValue &value, QGraphicsBlurEffect::BlurHint &out)
{
    out = qvariant_cast<QGraphicsBlurEffect::BlurHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsBlurEffect_BlurHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsBlurEffect::PerformanceHint) && (arg <= QGraphicsBlurEffect::AnimationHint))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsBlurEffect::BlurHint>(arg));
    return context->throwError(QString::fromLatin1("BlurHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsBlurEffect_BlurHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsBlurEffect::BlurHint value = qscriptvalue_cast<QGraphicsBlurEffect::BlurHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsBlurEffect_BlurHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsBlurEffect::BlurHint value = qscriptvalue_cast<QGraphicsBlurEffect::BlurHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsBlurEffect_BlurHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsBlurEffect_BlurHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsBlurEffect_BlurHint,
        qtscript_QGraphicsBlurEffect_BlurHint_valueOf, qtscript_QGraphicsBlurEffect_BlurHint_toString);
    qScriptRegisterMetaType<QGraphicsBlurEffect::BlurHint>(engine, qtscript_QGraphicsBlurEffect_BlurHint_toScriptValue,
        qtscript_QGraphicsBlurEffect_BlurHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsBlurEffect_BlurHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsBlurEffect_BlurHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsBlurEffect::BlurHints
//

static QScriptValue qtscript_QGraphicsBlurEffect_BlurHints_toScriptValue(QScriptEngine *engine, const QGraphicsBlurEffect::BlurHints &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QGraphicsBlurEffect_BlurHints_fromScriptValue(const QScriptValue &value, QGraphicsBlurEffect::BlurHints &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QGraphicsBlurEffect::BlurHints>())
        out = qvariant_cast<QGraphicsBlurEffect::BlurHints>(var);
    else if (var.userType() == qMetaTypeId<QGraphicsBlurEffect::BlurHint>())
        out = qvariant_cast<QGraphicsBlurEffect::BlurHint>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QGraphicsBlurEffect_BlurHints(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsBlurEffect::BlurHints result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QGraphicsBlurEffect::BlurHints>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QGraphicsBlurEffect::BlurHint>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("BlurHints(): argument %0 is not of type BlurHint").arg(i));
            }
            result |= qvariant_cast<QGraphicsBlurEffect::BlurHint>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QGraphicsBlurEffect_BlurHints_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsBlurEffect::BlurHints value = qscriptvalue_cast<QGraphicsBlurEffect::BlurHints>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsBlurEffect_BlurHints_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsBlurEffect::BlurHints value = qscriptvalue_cast<QGraphicsBlurEffect::BlurHints>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QGraphicsBlurEffect_BlurHint_values[i]) == qtscript_QGraphicsBlurEffect_BlurHint_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QGraphicsBlurEffect_BlurHint_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QGraphicsBlurEffect_BlurHints_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QGraphicsBlurEffect::BlurHints>() == otherObj.value<QGraphicsBlurEffect::BlurHints>())));
}

static QScriptValue qtscript_create_QGraphicsBlurEffect_BlurHints_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QGraphicsBlurEffect_BlurHints, qtscript_QGraphicsBlurEffect_BlurHints_valueOf,
        qtscript_QGraphicsBlurEffect_BlurHints_toString, qtscript_QGraphicsBlurEffect_BlurHints_equals);
    qScriptRegisterMetaType<QGraphicsBlurEffect::BlurHints>(engine, qtscript_QGraphicsBlurEffect_BlurHints_toScriptValue,
        qtscript_QGraphicsBlurEffect_BlurHints_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QGraphicsBlurEffect
//

static QScriptValue qtscript_QGraphicsBlurEffect_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsBlurEffect* _q_self = qscriptvalue_cast<QGraphicsBlurEffect*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsBlurEffect.%0(): this object is not a QGraphicsBlurEffect")
            .arg(qtscript_QGraphicsBlurEffect_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QGraphicsBlurEffect");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsBlurEffect_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsBlurEffect_function_names[_id+1],
        qtscript_QGraphicsBlurEffect_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsBlurEffect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsBlurEffect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsBlurEffect* _q_cpp_result = new QtScriptShell_QGraphicsBlurEffect();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsBlurEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QGraphicsBlurEffect* _q_cpp_result = new QtScriptShell_QGraphicsBlurEffect(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsBlurEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsBlurEffect_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsBlurEffect_function_names[_id],
        qtscript_QGraphicsBlurEffect_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsBlurEffect_toScriptValue(QScriptEngine *engine, QGraphicsBlurEffect* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsBlurEffect_fromScriptValue(const QScriptValue &value, QGraphicsBlurEffect* &out)
{
    out = qobject_cast<QGraphicsBlurEffect*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsBlurEffect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsBlurEffect*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsBlurEffect*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsEffect*>()));

    qScriptRegisterMetaType<QGraphicsBlurEffect*>(engine, qtscript_QGraphicsBlurEffect_toScriptValue, 
        qtscript_QGraphicsBlurEffect_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsBlurEffect_static_call, proto, qtscript_QGraphicsBlurEffect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("BlurHint"),
        qtscript_create_QGraphicsBlurEffect_BlurHint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BlurHints"),
        qtscript_create_QGraphicsBlurEffect_BlurHints_class(engine));
    return ctor;
}
