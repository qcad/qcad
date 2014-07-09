#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <quuid.h>
#include <QVariant>
#include <qbytearray.h>
#include <qdatastream.h>
#include <quuid.h>

#include "qtscriptshell_QUuid.h"

static const char * const qtscript_QUuid_function_names[] = {
    "QUuid"
    // static
    , "createUuid"
    , "fromRfc4122"
    // prototype
    , "isNull"
    , "equals"
    , "operator_less"
    , "readFrom"
    , "toByteArray"
    , "toRfc4122"
    , "toString"
    , "variant"
    , "version"
    , "writeTo"
};

static const char * const qtscript_QUuid_function_signatures[] = {
    "\nQByteArray arg__1\nString arg__1\nuint l, ushort w1, ushort w2, uchar b1, uchar b2, uchar b3, uchar b4, uchar b5, uchar b6, uchar b7, uchar b8"
    // static
    , ""
    , "QByteArray arg__1"
    // prototype
    , ""
    , "QUuid orig"
    , "QUuid other"
    , "QDataStream arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
};

static const int qtscript_QUuid_function_lengths[] = {
    11
    // static
    , 0
    , 1
    // prototype
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
};

static QScriptValue qtscript_QUuid_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUuid::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUuid)
Q_DECLARE_METATYPE(QUuid*)
Q_DECLARE_METATYPE(QtScriptShell_QUuid)
Q_DECLARE_METATYPE(QtScriptShell_QUuid*)
Q_DECLARE_METATYPE(QUuid::Variant)
Q_DECLARE_METATYPE(QUuid::Version)
Q_DECLARE_METATYPE(QDataStream*)

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
// QUuid::Variant
//

static const QUuid::Variant qtscript_QUuid_Variant_values[] = {
    QUuid::VarUnknown
    , QUuid::NCS
    , QUuid::DCE
    , QUuid::Microsoft
    , QUuid::Reserved
};

static const char * const qtscript_QUuid_Variant_keys[] = {
    "VarUnknown"
    , "NCS"
    , "DCE"
    , "Microsoft"
    , "Reserved"
};

static QString qtscript_QUuid_Variant_toStringHelper(QUuid::Variant value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QUuid_Variant_values[i] == value)
            return QString::fromLatin1(qtscript_QUuid_Variant_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QUuid_Variant_toScriptValue(QScriptEngine *engine, const QUuid::Variant &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QUuid"));
    return clazz.property(qtscript_QUuid_Variant_toStringHelper(value));
}

static void qtscript_QUuid_Variant_fromScriptValue(const QScriptValue &value, QUuid::Variant &out)
{
    out = qvariant_cast<QUuid::Variant>(value.toVariant());
}

static QScriptValue qtscript_construct_QUuid_Variant(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QUuid_Variant_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QUuid::Variant>(arg));
    }
    return context->throwError(QString::fromLatin1("Variant(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QUuid_Variant_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUuid::Variant value = qscriptvalue_cast<QUuid::Variant>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUuid_Variant_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUuid::Variant value = qscriptvalue_cast<QUuid::Variant>(context->thisObject());
    return QScriptValue(engine, qtscript_QUuid_Variant_toStringHelper(value));
}

static QScriptValue qtscript_create_QUuid_Variant_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QUuid_Variant,
        qtscript_QUuid_Variant_valueOf, qtscript_QUuid_Variant_toString);
    qScriptRegisterMetaType<QUuid::Variant>(engine, qtscript_QUuid_Variant_toScriptValue,
        qtscript_QUuid_Variant_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QUuid_Variant_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QUuid_Variant_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QUuid::Version
//

static const QUuid::Version qtscript_QUuid_Version_values[] = {
    QUuid::VerUnknown
    , QUuid::Time
    , QUuid::EmbeddedPOSIX
    , QUuid::Name
    , QUuid::Random
};

static const char * const qtscript_QUuid_Version_keys[] = {
    "VerUnknown"
    , "Time"
    , "EmbeddedPOSIX"
    , "Name"
    , "Random"
};

static QString qtscript_QUuid_Version_toStringHelper(QUuid::Version value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QUuid_Version_values[i] == value)
            return QString::fromLatin1(qtscript_QUuid_Version_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QUuid_Version_toScriptValue(QScriptEngine *engine, const QUuid::Version &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QUuid"));
    return clazz.property(qtscript_QUuid_Version_toStringHelper(value));
}

static void qtscript_QUuid_Version_fromScriptValue(const QScriptValue &value, QUuid::Version &out)
{
    out = qvariant_cast<QUuid::Version>(value.toVariant());
}

static QScriptValue qtscript_construct_QUuid_Version(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QUuid_Version_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QUuid::Version>(arg));
    }
    return context->throwError(QString::fromLatin1("Version(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QUuid_Version_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUuid::Version value = qscriptvalue_cast<QUuid::Version>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUuid_Version_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUuid::Version value = qscriptvalue_cast<QUuid::Version>(context->thisObject());
    return QScriptValue(engine, qtscript_QUuid_Version_toStringHelper(value));
}

static QScriptValue qtscript_create_QUuid_Version_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QUuid_Version,
        qtscript_QUuid_Version_valueOf, qtscript_QUuid_Version_toString);
    qScriptRegisterMetaType<QUuid::Version>(engine, qtscript_QUuid_Version_toScriptValue,
        qtscript_QUuid_Version_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QUuid_Version_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QUuid_Version_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QUuid
//

static QScriptValue qtscript_QUuid_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUuid* _q_self = qscriptvalue_cast<QUuid*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUuid.%0(): this object is not a QUuid")
            .arg(qtscript_QUuid_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QUuid _q_arg0 = qscriptvalue_cast<QUuid>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QUuid _q_arg0 = qscriptvalue_cast<QUuid>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toByteArray();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toRfc4122();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QUuid::Variant _q_result = _q_self->variant();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QUuid::Version _q_result = _q_self->version();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUuid_throw_ambiguity_error_helper(context,
        qtscript_QUuid_function_names[_id+3],
        qtscript_QUuid_function_signatures[_id+3]);
}

static QScriptValue qtscript_QUuid_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUuid(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QUuid _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUuid)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QtScriptShell_QUuid _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUuid)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QUuid _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUuid)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 11) {
        uint _q_arg0 = context->argument(0).toUInt32();
        ushort _q_arg1 = qscriptvalue_cast<ushort>(context->argument(1));
        ushort _q_arg2 = qscriptvalue_cast<ushort>(context->argument(2));
        uchar _q_arg3 = qscriptvalue_cast<uchar>(context->argument(3));
        uchar _q_arg4 = qscriptvalue_cast<uchar>(context->argument(4));
        uchar _q_arg5 = qscriptvalue_cast<uchar>(context->argument(5));
        uchar _q_arg6 = qscriptvalue_cast<uchar>(context->argument(6));
        uchar _q_arg7 = qscriptvalue_cast<uchar>(context->argument(7));
        uchar _q_arg8 = qscriptvalue_cast<uchar>(context->argument(8));
        uchar _q_arg9 = qscriptvalue_cast<uchar>(context->argument(9));
        uchar _q_arg10 = qscriptvalue_cast<uchar>(context->argument(10));
        QtScriptShell_QUuid _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8, _q_arg9, _q_arg10);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUuid)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QUuid _q_result = QUuid::createUuid();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QUuid _q_result = QUuid::fromRfc4122(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUuid_throw_ambiguity_error_helper(context,
        qtscript_QUuid_function_names[_id],
        qtscript_QUuid_function_signatures[_id]);
}

QScriptValue qtscript_create_QUuid_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUuid*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUuid*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUuid_prototype_call, qtscript_QUuid_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUuid_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QUuid>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QUuid*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUuid_static_call, proto, qtscript_QUuid_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUuid_static_call,
            qtscript_QUuid_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QUuid_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Variant"),
        qtscript_create_QUuid_Variant_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Version"),
        qtscript_create_QUuid_Version_class(engine, ctor));
    return ctor;
}
