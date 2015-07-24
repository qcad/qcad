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

#include "qtscriptshell_QDoubleValidator.h"

static const char * const qtscript_QDoubleValidator_function_names[] = {
    "QDoubleValidator"
    // static
    // prototype
    , "setRange"
    , "toString"
};

static const char * const qtscript_QDoubleValidator_function_signatures[] = {
    "QObject parent\ndouble bottom, double top, int decimals, QObject parent"
    // static
    // prototype
    , "double bottom, double top, int decimals"
""
};

static const int qtscript_QDoubleValidator_function_lengths[] = {
    4
    // static
    // prototype
    , 3
    , 0
};

static QScriptValue qtscript_QDoubleValidator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDoubleValidator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QDoubleValidator_metaObject()
{
    return &QDoubleValidator::staticMetaObject;
}

Q_DECLARE_METATYPE(QDoubleValidator*)
Q_DECLARE_METATYPE(QtScriptShell_QDoubleValidator*)
Q_DECLARE_METATYPE(QDoubleValidator::Notation)
Q_DECLARE_METATYPE(QValidator*)

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
// QDoubleValidator::Notation
//

static const QDoubleValidator::Notation qtscript_QDoubleValidator_Notation_values[] = {
    QDoubleValidator::StandardNotation
    , QDoubleValidator::ScientificNotation
};

static const char * const qtscript_QDoubleValidator_Notation_keys[] = {
    "StandardNotation"
    , "ScientificNotation"
};

static QString qtscript_QDoubleValidator_Notation_toStringHelper(QDoubleValidator::Notation value)
{
    const QMetaObject *meta = qtscript_QDoubleValidator_metaObject();
    int idx = meta->indexOfEnumerator("Notation");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QDoubleValidator_Notation_toScriptValue(QScriptEngine *engine, const QDoubleValidator::Notation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDoubleValidator"));
    return clazz.property(qtscript_QDoubleValidator_Notation_toStringHelper(value));
}

static void qtscript_QDoubleValidator_Notation_fromScriptValue(const QScriptValue &value, QDoubleValidator::Notation &out)
{
    out = qvariant_cast<QDoubleValidator::Notation>(value.toVariant());
}

static QScriptValue qtscript_construct_QDoubleValidator_Notation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QDoubleValidator_metaObject();
    int idx = meta->indexOfEnumerator("Notation");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QDoubleValidator::Notation>(arg));
    return context->throwError(QString::fromLatin1("Notation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDoubleValidator_Notation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDoubleValidator::Notation value = qscriptvalue_cast<QDoubleValidator::Notation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDoubleValidator_Notation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDoubleValidator::Notation value = qscriptvalue_cast<QDoubleValidator::Notation>(context->thisObject());
    return QScriptValue(engine, qtscript_QDoubleValidator_Notation_toStringHelper(value));
}

static QScriptValue qtscript_create_QDoubleValidator_Notation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDoubleValidator_Notation,
        qtscript_QDoubleValidator_Notation_valueOf, qtscript_QDoubleValidator_Notation_toString);
    qScriptRegisterMetaType<QDoubleValidator::Notation>(engine, qtscript_QDoubleValidator_Notation_toScriptValue,
        qtscript_QDoubleValidator_Notation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDoubleValidator_Notation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDoubleValidator_Notation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDoubleValidator
//

static QScriptValue qtscript_QDoubleValidator_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDoubleValidator* _q_self = qscriptvalue_cast<QDoubleValidator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDoubleValidator.%0(): this object is not a QDoubleValidator")
            .arg(qtscript_QDoubleValidator_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        double _q_arg0 = context->argument(0).toNumber();
        double _q_arg1 = context->argument(1).toNumber();
        _q_self->setRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        double _q_arg0 = context->argument(0).toNumber();
        double _q_arg1 = context->argument(1).toNumber();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setRange(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QDoubleValidator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDoubleValidator_throw_ambiguity_error_helper(context,
        qtscript_QDoubleValidator_function_names[_id+1],
        qtscript_QDoubleValidator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDoubleValidator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDoubleValidator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDoubleValidator* _q_cpp_result = new QtScriptShell_QDoubleValidator();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDoubleValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QDoubleValidator* _q_cpp_result = new QtScriptShell_QDoubleValidator(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDoubleValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        double _q_arg0 = context->argument(0).toNumber();
        double _q_arg1 = context->argument(1).toNumber();
        int _q_arg2 = context->argument(2).toInt32();
        QtScriptShell_QDoubleValidator* _q_cpp_result = new QtScriptShell_QDoubleValidator(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDoubleValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        double _q_arg0 = context->argument(0).toNumber();
        double _q_arg1 = context->argument(1).toNumber();
        int _q_arg2 = context->argument(2).toInt32();
        QObject* _q_arg3 = context->argument(3).toQObject();
        QtScriptShell_QDoubleValidator* _q_cpp_result = new QtScriptShell_QDoubleValidator(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDoubleValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDoubleValidator_throw_ambiguity_error_helper(context,
        qtscript_QDoubleValidator_function_names[_id],
        qtscript_QDoubleValidator_function_signatures[_id]);
}

static QScriptValue qtscript_QDoubleValidator_toScriptValue(QScriptEngine *engine, QDoubleValidator* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDoubleValidator_fromScriptValue(const QScriptValue &value, QDoubleValidator* &out)
{
    out = qobject_cast<QDoubleValidator*>(value.toQObject());
}

QScriptValue qtscript_create_QDoubleValidator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDoubleValidator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDoubleValidator*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QValidator*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDoubleValidator_prototype_call, qtscript_QDoubleValidator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDoubleValidator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDoubleValidator*>(engine, qtscript_QDoubleValidator_toScriptValue, 
        qtscript_QDoubleValidator_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDoubleValidator_static_call, proto, qtscript_QDoubleValidator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Notation"),
        qtscript_create_QDoubleValidator_Notation_class(engine, ctor));
    return ctor;
}
