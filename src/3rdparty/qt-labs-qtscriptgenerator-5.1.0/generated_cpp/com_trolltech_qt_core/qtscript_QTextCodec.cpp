#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextcodec.h>
#include <QTextCodec>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>
#include <qtextcodec.h>

#include "qtscriptshell_QTextCodec.h"

static const char * const qtscript_QTextCodec_function_names[] = {
    "QTextCodec"
    // static
    , "availableCodecs"
    , "availableMibs"
    , "codecForHtml"
    , "codecForLocale"
    , "codecForMib"
    , "codecForName"
    , "codecForUtfText"
    , "setCodecForLocale"
    // prototype
    , "aliases"
    , "canEncode"
    , "fromUnicode"
    , "makeDecoder"
    , "makeEncoder"
    , "mibEnum"
    , "name"
    , "toUnicode"
    , "toString"
};

static const char * const qtscript_QTextCodec_function_signatures[] = {
    ""
    // static
    , ""
    , ""
    , "QByteArray ba\nQByteArray ba, QTextCodec defaultCodec"
    , ""
    , "int mib"
    , "QByteArray name\nchar name"
    , "QByteArray ba\nQByteArray ba, QTextCodec defaultCodec"
    , "QTextCodec c"
    // prototype
    , ""
    , "char arg__1\nString arg__1"
    , "String uc"
    , "ConversionFlags flags"
    , "ConversionFlags flags"
    , ""
    , ""
    , "QByteArray arg__1"
""
};

static const int qtscript_QTextCodec_function_lengths[] = {
    0
    // static
    , 0
    , 0
    , 2
    , 0
    , 1
    , 1
    , 2
    , 1
    // prototype
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTextCodec_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextCodec::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QtScriptShell_QTextCodec*)
Q_DECLARE_METATYPE(QTextCodec::ConversionFlag)
Q_DECLARE_METATYPE(QFlags<QTextCodec::ConversionFlag>)
Q_DECLARE_METATYPE(QList<QByteArray >)
Q_DECLARE_METATYPE(QTextDecoder*)
Q_DECLARE_METATYPE(QTextEncoder*)
Q_DECLARE_METATYPE(QList<int >)
Q_DECLARE_METATYPE(const char*)

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
// QTextCodec::ConversionFlag
//

static const QTextCodec::ConversionFlag qtscript_QTextCodec_ConversionFlag_values[] = {
    QTextCodec::ConvertInvalidToNull
    , QTextCodec::DefaultConversion
    , QTextCodec::IgnoreHeader
    , QTextCodec::FreeFunction
};

static const char * const qtscript_QTextCodec_ConversionFlag_keys[] = {
    "ConvertInvalidToNull"
    , "DefaultConversion"
    , "IgnoreHeader"
    , "FreeFunction"
};

static QString qtscript_QTextCodec_ConversionFlag_toStringHelper(QTextCodec::ConversionFlag value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QTextCodec_ConversionFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QTextCodec_ConversionFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTextCodec_ConversionFlag_toScriptValue(QScriptEngine *engine, const QTextCodec::ConversionFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextCodec"));
    return clazz.property(qtscript_QTextCodec_ConversionFlag_toStringHelper(value));
}

static void qtscript_QTextCodec_ConversionFlag_fromScriptValue(const QScriptValue &value, QTextCodec::ConversionFlag &out)
{
    out = qvariant_cast<QTextCodec::ConversionFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextCodec_ConversionFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QTextCodec_ConversionFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTextCodec::ConversionFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("ConversionFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextCodec_ConversionFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextCodec::ConversionFlag value = qscriptvalue_cast<QTextCodec::ConversionFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextCodec_ConversionFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextCodec::ConversionFlag value = qscriptvalue_cast<QTextCodec::ConversionFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextCodec_ConversionFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextCodec_ConversionFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextCodec_ConversionFlag,
        qtscript_QTextCodec_ConversionFlag_valueOf, qtscript_QTextCodec_ConversionFlag_toString);
    qScriptRegisterMetaType<QTextCodec::ConversionFlag>(engine, qtscript_QTextCodec_ConversionFlag_toScriptValue,
        qtscript_QTextCodec_ConversionFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextCodec_ConversionFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextCodec_ConversionFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextCodec::ConversionFlags
//

static QScriptValue qtscript_QTextCodec_ConversionFlags_toScriptValue(QScriptEngine *engine, const QTextCodec::ConversionFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QTextCodec_ConversionFlags_fromScriptValue(const QScriptValue &value, QTextCodec::ConversionFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QTextCodec::ConversionFlags>())
        out = qvariant_cast<QTextCodec::ConversionFlags>(var);
    else if (var.userType() == qMetaTypeId<QTextCodec::ConversionFlag>())
        out = qvariant_cast<QTextCodec::ConversionFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QTextCodec_ConversionFlags(QScriptContext *context, QScriptEngine *engine)
{
    QTextCodec::ConversionFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QTextCodec::ConversionFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QTextCodec::ConversionFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ConversionFlags(): argument %0 is not of type ConversionFlag").arg(i));
            }
            result |= qvariant_cast<QTextCodec::ConversionFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QTextCodec_ConversionFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextCodec::ConversionFlags value = qscriptvalue_cast<QTextCodec::ConversionFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextCodec_ConversionFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextCodec::ConversionFlags value = qscriptvalue_cast<QTextCodec::ConversionFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QTextCodec_ConversionFlag_values[i]) == qtscript_QTextCodec_ConversionFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QTextCodec_ConversionFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QTextCodec_ConversionFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QTextCodec::ConversionFlags>() == otherObj.value<QTextCodec::ConversionFlags>())));
}

static QScriptValue qtscript_create_QTextCodec_ConversionFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QTextCodec_ConversionFlags, qtscript_QTextCodec_ConversionFlags_valueOf,
        qtscript_QTextCodec_ConversionFlags_toString, qtscript_QTextCodec_ConversionFlags_equals);
    qScriptRegisterMetaType<QTextCodec::ConversionFlags>(engine, qtscript_QTextCodec_ConversionFlags_toScriptValue,
        qtscript_QTextCodec_ConversionFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QTextCodec
//

static QScriptValue qtscript_QTextCodec_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextCodec* _q_self = qscriptvalue_cast<QTextCodec*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextCodec.%0(): this object is not a QTextCodec")
            .arg(qtscript_QTextCodec_function_names[_id+9]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = _q_self->aliases();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QChar>() == context->argument(0).toVariant().userType())) {
            QChar _q_arg0 = qscriptvalue_cast<QChar>(context->argument(0));
            bool _q_result = _q_self->canEncode(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->canEncode(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = _q_self->fromUnicode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QTextDecoder* _q_result = _q_self->makeDecoder();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<QTextCodec::ConversionFlag> _q_arg0 = qscriptvalue_cast<QFlags<QTextCodec::ConversionFlag> >(context->argument(0));
        QTextDecoder* _q_result = _q_self->makeDecoder(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTextEncoder* _q_result = _q_self->makeEncoder();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<QTextCodec::ConversionFlag> _q_arg0 = qscriptvalue_cast<QFlags<QTextCodec::ConversionFlag> >(context->argument(0));
        QTextEncoder* _q_result = _q_self->makeEncoder(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->mibEnum();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->name();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_result = _q_self->toUnicode(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QTextCodec");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextCodec_throw_ambiguity_error_helper(context,
        qtscript_QTextCodec_function_names[_id+9],
        qtscript_QTextCodec_function_signatures[_id+9]);
}

static QScriptValue qtscript_QTextCodec_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QTextCodec cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = QTextCodec::availableCodecs();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<int > _q_result = QTextCodec::availableMibs();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QTextCodec* _q_result = QTextCodec::codecForHtml(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QTextCodec* _q_arg1 = qscriptvalue_cast<QTextCodec*>(context->argument(1));
        QTextCodec* _q_result = QTextCodec::codecForHtml(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTextCodec* _q_result = QTextCodec::codecForLocale();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextCodec* _q_result = QTextCodec::codecForMib(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QTextCodec* _q_result = QTextCodec::codecForName(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QTextCodec* _q_result = QTextCodec::codecForName(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QTextCodec* _q_result = QTextCodec::codecForUtfText(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QTextCodec* _q_arg1 = qscriptvalue_cast<QTextCodec*>(context->argument(1));
        QTextCodec* _q_result = QTextCodec::codecForUtfText(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
        QTextCodec::setCodecForLocale(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextCodec_throw_ambiguity_error_helper(context,
        qtscript_QTextCodec_function_names[_id],
        qtscript_QTextCodec_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextCodec_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextCodec*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextCodec*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextCodec_prototype_call, qtscript_QTextCodec_function_lengths[i+9]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextCodec_function_names[i+9]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextCodec*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextCodec_static_call, proto, qtscript_QTextCodec_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextCodec_static_call,
            qtscript_QTextCodec_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QTextCodec_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ConversionFlag"),
        qtscript_create_QTextCodec_ConversionFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ConversionFlags"),
        qtscript_create_QTextCodec_ConversionFlags_class(engine));
    return ctor;
}
