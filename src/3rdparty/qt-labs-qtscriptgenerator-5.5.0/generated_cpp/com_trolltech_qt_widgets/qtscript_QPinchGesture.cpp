#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgesture.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpoint.h>

#include "qtscriptshell_QPinchGesture.h"

static const char * const qtscript_QPinchGesture_function_names[] = {
    "QPinchGesture"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QPinchGesture_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QPinchGesture_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QPinchGesture_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPinchGesture::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPinchGesture*)
Q_DECLARE_METATYPE(QtScriptShell_QPinchGesture*)
Q_DECLARE_METATYPE(QPinchGesture::ChangeFlag)
//Q_DECLARE_METATYPE(QFlags<QPinchGesture::ChangeFlag>)
Q_DECLARE_METATYPE(QGesture*)

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
// QPinchGesture::ChangeFlag
//

static const QPinchGesture::ChangeFlag qtscript_QPinchGesture_ChangeFlag_values[] = {
    QPinchGesture::ScaleFactorChanged
    , QPinchGesture::RotationAngleChanged
    , QPinchGesture::CenterPointChanged
};

static const char * const qtscript_QPinchGesture_ChangeFlag_keys[] = {
    "ScaleFactorChanged"
    , "RotationAngleChanged"
    , "CenterPointChanged"
};

static QString qtscript_QPinchGesture_ChangeFlag_toStringHelper(QPinchGesture::ChangeFlag value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QPinchGesture_ChangeFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QPinchGesture_ChangeFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QPinchGesture_ChangeFlag_toScriptValue(QScriptEngine *engine, const QPinchGesture::ChangeFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPinchGesture"));
    return clazz.property(qtscript_QPinchGesture_ChangeFlag_toStringHelper(value));
}

static void qtscript_QPinchGesture_ChangeFlag_fromScriptValue(const QScriptValue &value, QPinchGesture::ChangeFlag &out)
{
    out = qvariant_cast<QPinchGesture::ChangeFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QPinchGesture_ChangeFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QPinchGesture_ChangeFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QPinchGesture::ChangeFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("ChangeFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPinchGesture_ChangeFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPinchGesture::ChangeFlag value = qscriptvalue_cast<QPinchGesture::ChangeFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPinchGesture_ChangeFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPinchGesture::ChangeFlag value = qscriptvalue_cast<QPinchGesture::ChangeFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QPinchGesture_ChangeFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QPinchGesture_ChangeFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPinchGesture_ChangeFlag,
        qtscript_QPinchGesture_ChangeFlag_valueOf, qtscript_QPinchGesture_ChangeFlag_toString);
    qScriptRegisterMetaType<QPinchGesture::ChangeFlag>(engine, qtscript_QPinchGesture_ChangeFlag_toScriptValue,
        qtscript_QPinchGesture_ChangeFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPinchGesture_ChangeFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPinchGesture_ChangeFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPinchGesture::ChangeFlags
//

static QScriptValue qtscript_QPinchGesture_ChangeFlags_toScriptValue(QScriptEngine *engine, const QPinchGesture::ChangeFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QPinchGesture_ChangeFlags_fromScriptValue(const QScriptValue &value, QPinchGesture::ChangeFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QPinchGesture::ChangeFlags>())
        out = qvariant_cast<QPinchGesture::ChangeFlags>(var);
    else if (var.userType() == qMetaTypeId<QPinchGesture::ChangeFlag>())
        out = qvariant_cast<QPinchGesture::ChangeFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QPinchGesture_ChangeFlags(QScriptContext *context, QScriptEngine *engine)
{
    QPinchGesture::ChangeFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QPinchGesture::ChangeFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QPinchGesture::ChangeFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ChangeFlags(): argument %0 is not of type ChangeFlag").arg(i));
            }
            result |= qvariant_cast<QPinchGesture::ChangeFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QPinchGesture_ChangeFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPinchGesture::ChangeFlags value = qscriptvalue_cast<QPinchGesture::ChangeFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPinchGesture_ChangeFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPinchGesture::ChangeFlags value = qscriptvalue_cast<QPinchGesture::ChangeFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QPinchGesture_ChangeFlag_values[i]) == qtscript_QPinchGesture_ChangeFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QPinchGesture_ChangeFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QPinchGesture_ChangeFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QPinchGesture::ChangeFlags>() == otherObj.value<QPinchGesture::ChangeFlags>())));
}

static QScriptValue qtscript_create_QPinchGesture_ChangeFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QPinchGesture_ChangeFlags, qtscript_QPinchGesture_ChangeFlags_valueOf,
        qtscript_QPinchGesture_ChangeFlags_toString, qtscript_QPinchGesture_ChangeFlags_equals);
    qScriptRegisterMetaType<QPinchGesture::ChangeFlags>(engine, qtscript_QPinchGesture_ChangeFlags_toScriptValue,
        qtscript_QPinchGesture_ChangeFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QPinchGesture
//

static QScriptValue qtscript_QPinchGesture_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPinchGesture* _q_self = qscriptvalue_cast<QPinchGesture*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPinchGesture.%0(): this object is not a QPinchGesture")
            .arg(qtscript_QPinchGesture_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QPinchGesture");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPinchGesture_throw_ambiguity_error_helper(context,
        qtscript_QPinchGesture_function_names[_id+1],
        qtscript_QPinchGesture_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPinchGesture_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPinchGesture(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPinchGesture* _q_cpp_result = new QtScriptShell_QPinchGesture();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPinchGesture*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QPinchGesture* _q_cpp_result = new QtScriptShell_QPinchGesture(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPinchGesture*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPinchGesture_throw_ambiguity_error_helper(context,
        qtscript_QPinchGesture_function_names[_id],
        qtscript_QPinchGesture_function_signatures[_id]);
}

static QScriptValue qtscript_QPinchGesture_toScriptValue(QScriptEngine *engine, QPinchGesture* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPinchGesture_fromScriptValue(const QScriptValue &value, QPinchGesture* &out)
{
    out = qobject_cast<QPinchGesture*>(value.toQObject());
}

QScriptValue qtscript_create_QPinchGesture_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPinchGesture*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPinchGesture*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGesture*>()));

    qScriptRegisterMetaType<QPinchGesture*>(engine, qtscript_QPinchGesture_toScriptValue, 
        qtscript_QPinchGesture_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPinchGesture_static_call, proto, qtscript_QPinchGesture_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ChangeFlag"),
        qtscript_create_QPinchGesture_ChangeFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ChangeFlags"),
        qtscript_create_QPinchGesture_ChangeFlags_class(engine));
    return ctor;
}
