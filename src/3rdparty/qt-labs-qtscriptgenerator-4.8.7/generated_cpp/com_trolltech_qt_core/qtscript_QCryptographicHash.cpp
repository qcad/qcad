#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcryptographichash.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcryptographichash.h>

static const char * const qtscript_QCryptographicHash_function_names[] = {
    "QCryptographicHash"
    // static
    , "hash"
    // prototype
    , "addData"
    , "reset"
    , "result"
    , "toString"
};

static const char * const qtscript_QCryptographicHash_function_signatures[] = {
    "Algorithm method"
    // static
    , "QByteArray data, Algorithm method"
    // prototype
    , "QByteArray data"
    , ""
    , ""
""
};

static const int qtscript_QCryptographicHash_function_lengths[] = {
    1
    // static
    , 2
    // prototype
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QCryptographicHash_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QCryptographicHash::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QCryptographicHash*)
Q_DECLARE_METATYPE(QCryptographicHash::Algorithm)

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
// QCryptographicHash::Algorithm
//

static const QCryptographicHash::Algorithm qtscript_QCryptographicHash_Algorithm_values[] = {
    QCryptographicHash::Md4
    , QCryptographicHash::Md5
    , QCryptographicHash::Sha1
};

static const char * const qtscript_QCryptographicHash_Algorithm_keys[] = {
    "Md4"
    , "Md5"
    , "Sha1"
};

static QString qtscript_QCryptographicHash_Algorithm_toStringHelper(QCryptographicHash::Algorithm value)
{
    if ((value >= QCryptographicHash::Md4) && (value <= QCryptographicHash::Sha1))
        return qtscript_QCryptographicHash_Algorithm_keys[static_cast<int>(value)-static_cast<int>(QCryptographicHash::Md4)];
    return QString();
}

static QScriptValue qtscript_QCryptographicHash_Algorithm_toScriptValue(QScriptEngine *engine, const QCryptographicHash::Algorithm &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QCryptographicHash"));
    return clazz.property(qtscript_QCryptographicHash_Algorithm_toStringHelper(value));
}

static void qtscript_QCryptographicHash_Algorithm_fromScriptValue(const QScriptValue &value, QCryptographicHash::Algorithm &out)
{
    out = qvariant_cast<QCryptographicHash::Algorithm>(value.toVariant());
}

static QScriptValue qtscript_construct_QCryptographicHash_Algorithm(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QCryptographicHash::Md4) && (arg <= QCryptographicHash::Sha1))
        return qScriptValueFromValue(engine,  static_cast<QCryptographicHash::Algorithm>(arg));
    return context->throwError(QString::fromLatin1("Algorithm(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QCryptographicHash_Algorithm_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QCryptographicHash::Algorithm value = qscriptvalue_cast<QCryptographicHash::Algorithm>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QCryptographicHash_Algorithm_toString(QScriptContext *context, QScriptEngine *engine)
{
    QCryptographicHash::Algorithm value = qscriptvalue_cast<QCryptographicHash::Algorithm>(context->thisObject());
    return QScriptValue(engine, qtscript_QCryptographicHash_Algorithm_toStringHelper(value));
}

static QScriptValue qtscript_create_QCryptographicHash_Algorithm_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QCryptographicHash_Algorithm,
        qtscript_QCryptographicHash_Algorithm_valueOf, qtscript_QCryptographicHash_Algorithm_toString);
    qScriptRegisterMetaType<QCryptographicHash::Algorithm>(engine, qtscript_QCryptographicHash_Algorithm_toScriptValue,
        qtscript_QCryptographicHash_Algorithm_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QCryptographicHash_Algorithm_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QCryptographicHash_Algorithm_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QCryptographicHash
//

static QScriptValue qtscript_QCryptographicHash_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QCryptographicHash* _q_self = qscriptvalue_cast<QCryptographicHash*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QCryptographicHash.%0(): this object is not a QCryptographicHash")
            .arg(qtscript_QCryptographicHash_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->addData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->result();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QCryptographicHash");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCryptographicHash_throw_ambiguity_error_helper(context,
        qtscript_QCryptographicHash_function_names[_id+2],
        qtscript_QCryptographicHash_function_signatures[_id+2]);
}

static QScriptValue qtscript_QCryptographicHash_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QCryptographicHash(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QCryptographicHash::Algorithm _q_arg0 = qscriptvalue_cast<QCryptographicHash::Algorithm>(context->argument(0));
        QCryptographicHash* _q_cpp_result = new QCryptographicHash(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QCryptographicHash::Algorithm _q_arg1 = qscriptvalue_cast<QCryptographicHash::Algorithm>(context->argument(1));
        QByteArray _q_result = QCryptographicHash::hash(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCryptographicHash_throw_ambiguity_error_helper(context,
        qtscript_QCryptographicHash_function_names[_id],
        qtscript_QCryptographicHash_function_signatures[_id]);
}

QScriptValue qtscript_create_QCryptographicHash_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QCryptographicHash*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QCryptographicHash*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCryptographicHash_prototype_call, qtscript_QCryptographicHash_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QCryptographicHash_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QCryptographicHash*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QCryptographicHash_static_call, proto, qtscript_QCryptographicHash_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCryptographicHash_static_call,
            qtscript_QCryptographicHash_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QCryptographicHash_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Algorithm"),
        qtscript_create_QCryptographicHash_Algorithm_class(engine, ctor));
    return ctor;
}
