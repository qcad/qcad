#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qvalidator.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocale.h>
#include <qobject.h>
#include <qvalidator.h>

#include "qtscriptshell_QValidator.h"

static const char * const qtscript_QValidator_function_names[] = {
    "QValidator"
    // static
    // prototype
    , "fixup"
    , "locale"
    , "setLocale"
    , "validate"
    , "toString"
};

static const char * const qtscript_QValidator_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String arg__1"
    , ""
    , "QLocale locale"
    , "String arg__1, int arg__2"
""
};

static const int qtscript_QValidator_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QValidator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QValidator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QValidator*)
Q_DECLARE_METATYPE(QtScriptShell_QValidator*)
Q_DECLARE_METATYPE(QValidator::State)

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
// QValidator::State
//

static const QValidator::State qtscript_QValidator_State_values[] = {
    QValidator::Invalid
    , QValidator::Intermediate
    , QValidator::Acceptable
};

static const char * const qtscript_QValidator_State_keys[] = {
    "Invalid"
    , "Intermediate"
    , "Acceptable"
};

static QString qtscript_QValidator_State_toStringHelper(QValidator::State value)
{
    if ((value >= QValidator::Invalid) && (value <= QValidator::Acceptable))
        return qtscript_QValidator_State_keys[static_cast<int>(value)-static_cast<int>(QValidator::Invalid)];
    return QString();
}

static QScriptValue qtscript_QValidator_State_toScriptValue(QScriptEngine *engine, const QValidator::State &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QValidator"));
    return clazz.property(qtscript_QValidator_State_toStringHelper(value));
}

static void qtscript_QValidator_State_fromScriptValue(const QScriptValue &value, QValidator::State &out)
{
    out = qvariant_cast<QValidator::State>(value.toVariant());
}

static QScriptValue qtscript_construct_QValidator_State(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QValidator::Invalid) && (arg <= QValidator::Acceptable))
        return qScriptValueFromValue(engine,  static_cast<QValidator::State>(arg));
    return context->throwError(QString::fromLatin1("State(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QValidator_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QValidator::State value = qscriptvalue_cast<QValidator::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QValidator_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QValidator::State value = qscriptvalue_cast<QValidator::State>(context->thisObject());
    return QScriptValue(engine, qtscript_QValidator_State_toStringHelper(value));
}

static QScriptValue qtscript_create_QValidator_State_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QValidator_State,
        qtscript_QValidator_State_valueOf, qtscript_QValidator_State_toString);
    qScriptRegisterMetaType<QValidator::State>(engine, qtscript_QValidator_State_toScriptValue,
        qtscript_QValidator_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QValidator_State_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QValidator_State_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QValidator
//

static QScriptValue qtscript_QValidator_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QValidator* _q_self = qscriptvalue_cast<QValidator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QValidator.%0(): this object is not a QValidator")
            .arg(qtscript_QValidator_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->fixup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QLocale _q_result = _q_self->locale();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
        _q_self->setLocale(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QValidator::State _q_result = _q_self->validate(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QValidator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QValidator_throw_ambiguity_error_helper(context,
        qtscript_QValidator_function_names[_id+1],
        qtscript_QValidator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QValidator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QValidator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QValidator* _q_cpp_result = new QtScriptShell_QValidator();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QValidator* _q_cpp_result = new QtScriptShell_QValidator(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QValidator_throw_ambiguity_error_helper(context,
        qtscript_QValidator_function_names[_id],
        qtscript_QValidator_function_signatures[_id]);
}

static QScriptValue qtscript_QValidator_toScriptValue(QScriptEngine *engine, QValidator* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QValidator_fromScriptValue(const QScriptValue &value, QValidator* &out)
{
    out = qobject_cast<QValidator*>(value.toQObject());
}

QScriptValue qtscript_create_QValidator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QValidator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QValidator*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QValidator_prototype_call, qtscript_QValidator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QValidator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QValidator*>(engine, qtscript_QValidator_toScriptValue, 
        qtscript_QValidator_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QValidator_static_call, proto, qtscript_QValidator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QValidator_State_class(engine, ctor));
    return ctor;
}
