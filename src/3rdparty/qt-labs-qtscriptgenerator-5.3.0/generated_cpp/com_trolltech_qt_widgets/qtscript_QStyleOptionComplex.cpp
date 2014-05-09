#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstyleoption.h>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QStyleOptionComplex.h"

static const char * const qtscript_QStyleOptionComplex_function_names[] = {
    "QStyleOptionComplex"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionComplex_function_signatures[] = {
    "QStyleOptionComplex other\nint version, int type"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionComplex_function_lengths[] = {
    2
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionComplex_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionComplex::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionComplex)
Q_DECLARE_METATYPE(QStyleOptionComplex*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionComplex)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionComplex*)
Q_DECLARE_METATYPE(QStyleOptionComplex::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionComplex::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOption*)

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
// QStyleOptionComplex::StyleOptionType
//

static const QStyleOptionComplex::StyleOptionType qtscript_QStyleOptionComplex_StyleOptionType_values[] = {
    QStyleOptionComplex::Type
};

static const char * const qtscript_QStyleOptionComplex_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionComplex_StyleOptionType_toStringHelper(QStyleOptionComplex::StyleOptionType value)
{
    if ((value >= QStyleOptionComplex::Type) && (value <= QStyleOptionComplex::Type))
        return qtscript_QStyleOptionComplex_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionComplex::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionComplex_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionComplex::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionComplex"));
    return clazz.property(qtscript_QStyleOptionComplex_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionComplex_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionComplex::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionComplex::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionComplex_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionComplex::Type) && (arg <= QStyleOptionComplex::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionComplex::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionComplex_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComplex::StyleOptionType value = qscriptvalue_cast<QStyleOptionComplex::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionComplex_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComplex::StyleOptionType value = qscriptvalue_cast<QStyleOptionComplex::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionComplex_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionComplex_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionComplex_StyleOptionType,
        qtscript_QStyleOptionComplex_StyleOptionType_valueOf, qtscript_QStyleOptionComplex_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionComplex::StyleOptionType>(engine, qtscript_QStyleOptionComplex_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionComplex_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionComplex_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionComplex_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionComplex::StyleOptionVersion
//

static const QStyleOptionComplex::StyleOptionVersion qtscript_QStyleOptionComplex_StyleOptionVersion_values[] = {
    QStyleOptionComplex::Version
};

static const char * const qtscript_QStyleOptionComplex_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionComplex_StyleOptionVersion_toStringHelper(QStyleOptionComplex::StyleOptionVersion value)
{
    if ((value >= QStyleOptionComplex::Version) && (value <= QStyleOptionComplex::Version))
        return qtscript_QStyleOptionComplex_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionComplex::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionComplex_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionComplex::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionComplex"));
    return clazz.property(qtscript_QStyleOptionComplex_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionComplex_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionComplex::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionComplex::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionComplex_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionComplex::Version) && (arg <= QStyleOptionComplex::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionComplex::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionComplex_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComplex::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionComplex::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionComplex_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComplex::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionComplex::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionComplex_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionComplex_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionComplex_StyleOptionVersion,
        qtscript_QStyleOptionComplex_StyleOptionVersion_valueOf, qtscript_QStyleOptionComplex_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionComplex::StyleOptionVersion>(engine, qtscript_QStyleOptionComplex_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionComplex_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionComplex_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionComplex_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionComplex
//

static QScriptValue qtscript_QStyleOptionComplex_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionComplex* _q_self = qscriptvalue_cast<QStyleOptionComplex*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionComplex.%0(): this object is not a QStyleOptionComplex")
            .arg(qtscript_QStyleOptionComplex_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionComplex");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionComplex_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionComplex_function_names[_id+1],
        qtscript_QStyleOptionComplex_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionComplex_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionComplex(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionComplex _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionComplex)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QStyleOptionComplex>() == context->argument(0).toVariant().userType())) {
            QStyleOptionComplex _q_arg0 = qscriptvalue_cast<QStyleOptionComplex>(context->argument(0));
            QtScriptShell_QStyleOptionComplex _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionComplex)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QtScriptShell_QStyleOptionComplex _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionComplex)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QStyleOptionComplex _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionComplex)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionComplex_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionComplex_function_names[_id],
        qtscript_QStyleOptionComplex_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionComplex_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionComplex*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionComplex*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOption*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionComplex>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionComplex*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionComplex_static_call, proto, qtscript_QStyleOptionComplex_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionComplex_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionComplex_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
