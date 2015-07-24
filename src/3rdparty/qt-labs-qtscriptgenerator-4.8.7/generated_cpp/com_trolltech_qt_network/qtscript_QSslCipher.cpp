#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsslcipher.h>
#include <QVariant>
#include <qsslcipher.h>

static const char * const qtscript_QSslCipher_function_names[] = {
    "QSslCipher"
    // static
    // prototype
    , "authenticationMethod"
    , "encryptionMethod"
    , "isNull"
    , "keyExchangeMethod"
    , "name"
    , "operator_assign"
    , "equals"
    , "protocol"
    , "protocolString"
    , "supportedBits"
    , "usedBits"
    , "toString"
};

static const char * const qtscript_QSslCipher_function_signatures[] = {
    "\nQSslCipher other\nString name, SslProtocol protocol"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QSslCipher other"
    , "QSslCipher other"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QSslCipher_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSslCipher_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSslCipher::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSslCipher)
Q_DECLARE_METATYPE(QSslCipher*)
Q_DECLARE_METATYPE(QSsl::SslProtocol)

//
// QSslCipher
//

static QScriptValue qtscript_QSslCipher_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSslCipher* _q_self = qscriptvalue_cast<QSslCipher*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSslCipher.%0(): this object is not a QSslCipher")
            .arg(qtscript_QSslCipher_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->authenticationMethod();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->encryptionMethod();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->keyExchangeMethod();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QSslCipher _q_arg0 = qscriptvalue_cast<QSslCipher>(context->argument(0));
        QSslCipher _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QSslCipher _q_arg0 = qscriptvalue_cast<QSslCipher>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QSsl::SslProtocol _q_result = _q_self->protocol();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->protocolString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->supportedBits();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->usedBits();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslCipher_throw_ambiguity_error_helper(context,
        qtscript_QSslCipher_function_names[_id+1],
        qtscript_QSslCipher_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSslCipher_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSslCipher(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSslCipher _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QSslCipher _q_arg0 = qscriptvalue_cast<QSslCipher>(context->argument(0));
        QSslCipher _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::SslProtocol _q_arg1 = qscriptvalue_cast<QSsl::SslProtocol>(context->argument(1));
        QSslCipher _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslCipher_throw_ambiguity_error_helper(context,
        qtscript_QSslCipher_function_names[_id],
        qtscript_QSslCipher_function_signatures[_id]);
}

QScriptValue qtscript_create_QSslCipher_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSslCipher*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSslCipher*)0));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslCipher_prototype_call, qtscript_QSslCipher_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSslCipher_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSslCipher>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSslCipher*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSslCipher_static_call, proto, qtscript_QSslCipher_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
