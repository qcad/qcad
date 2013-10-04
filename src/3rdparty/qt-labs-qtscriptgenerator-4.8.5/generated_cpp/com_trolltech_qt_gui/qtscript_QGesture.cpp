#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgesture.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpoint.h>

#include "qtscriptshell_QGesture.h"

static const char * const qtscript_QGesture_function_names[] = {
    "QGesture"
    // static
    // prototype
    , "unsetHotSpot"
    , "toString"
};

static const char * const qtscript_QGesture_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
""
};

static const int qtscript_QGesture_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QGesture_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGesture::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGesture*)
Q_DECLARE_METATYPE(QtScriptShell_QGesture*)

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
// QGesture::GestureCancelPolicy
//

static const QGesture::GestureCancelPolicy qtscript_QGesture_GestureCancelPolicy_values[] = {
    QGesture::CancelNone
    , QGesture::CancelAllInContext
};

static const char * const qtscript_QGesture_GestureCancelPolicy_keys[] = {
    "CancelNone"
    , "CancelAllInContext"
};

static QString qtscript_QGesture_GestureCancelPolicy_toStringHelper(QGesture::GestureCancelPolicy value)
{
    if ((value >= QGesture::CancelNone) && (value <= QGesture::CancelAllInContext))
        return qtscript_QGesture_GestureCancelPolicy_keys[static_cast<int>(value)-static_cast<int>(QGesture::CancelNone)];
    return QString();
}

static QScriptValue qtscript_QGesture_GestureCancelPolicy_toScriptValue(QScriptEngine *engine, const QGesture::GestureCancelPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGesture"));
    return clazz.property(qtscript_QGesture_GestureCancelPolicy_toStringHelper(value));
}

static void qtscript_QGesture_GestureCancelPolicy_fromScriptValue(const QScriptValue &value, QGesture::GestureCancelPolicy &out)
{
    out = qvariant_cast<QGesture::GestureCancelPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QGesture_GestureCancelPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGesture::CancelNone) && (arg <= QGesture::CancelAllInContext))
        return qScriptValueFromValue(engine,  static_cast<QGesture::GestureCancelPolicy>(arg));
    return context->throwError(QString::fromLatin1("GestureCancelPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGesture_GestureCancelPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGesture::GestureCancelPolicy value = qscriptvalue_cast<QGesture::GestureCancelPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGesture_GestureCancelPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGesture::GestureCancelPolicy value = qscriptvalue_cast<QGesture::GestureCancelPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QGesture_GestureCancelPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QGesture_GestureCancelPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGesture_GestureCancelPolicy,
        qtscript_QGesture_GestureCancelPolicy_valueOf, qtscript_QGesture_GestureCancelPolicy_toString);
    qScriptRegisterMetaType<QGesture::GestureCancelPolicy>(engine, qtscript_QGesture_GestureCancelPolicy_toScriptValue,
        qtscript_QGesture_GestureCancelPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGesture_GestureCancelPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGesture_GestureCancelPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGesture
//

static QScriptValue qtscript_QGesture_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGesture* _q_self = qscriptvalue_cast<QGesture*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGesture.%0(): this object is not a QGesture")
            .arg(qtscript_QGesture_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->unsetHotSpot();
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QGesture");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGesture_throw_ambiguity_error_helper(context,
        qtscript_QGesture_function_names[_id+1],
        qtscript_QGesture_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGesture_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGesture(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGesture* _q_cpp_result = new QtScriptShell_QGesture();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGesture*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QGesture* _q_cpp_result = new QtScriptShell_QGesture(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGesture*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGesture_throw_ambiguity_error_helper(context,
        qtscript_QGesture_function_names[_id],
        qtscript_QGesture_function_signatures[_id]);
}

static QScriptValue qtscript_QGesture_toScriptValue(QScriptEngine *engine, QGesture* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGesture_fromScriptValue(const QScriptValue &value, QGesture* &out)
{
    out = qobject_cast<QGesture*>(value.toQObject());
}

QScriptValue qtscript_create_QGesture_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGesture*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGesture*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGesture_prototype_call, qtscript_QGesture_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGesture_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGesture*>(engine, qtscript_QGesture_toScriptValue, 
        qtscript_QGesture_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGesture_static_call, proto, qtscript_QGesture_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("GestureCancelPolicy"),
        qtscript_create_QGesture_GestureCancelPolicy_class(engine, ctor));
    return ctor;
}
