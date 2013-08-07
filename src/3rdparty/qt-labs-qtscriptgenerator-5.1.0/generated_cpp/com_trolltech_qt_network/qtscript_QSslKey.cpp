#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsslkey.h>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qsslkey.h>

static const char * const qtscript_QSslKey_function_names[] = {
    "QSslKey"
    // static
    // prototype
    , "algorithm"
    , "clear"
    , "handle"
    , "isNull"
    , "length"
    , "operator_assign"
    , "equals"
    , "swap"
    , "toDer"
    , "toPem"
    , "type"
    , "toString"
};

static const char * const qtscript_QSslKey_function_signatures[] = {
    "\nQIODevice device, KeyAlgorithm algorithm, EncodingFormat format, KeyType type, QByteArray passPhrase\nQt::HANDLE handle, KeyType type\nQByteArray encoded, KeyAlgorithm algorithm, EncodingFormat format, KeyType type, QByteArray passPhrase\nQSslKey other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QSslKey other"
    , "QSslKey key"
    , "QSslKey other"
    , "QByteArray passPhrase"
    , "QByteArray passPhrase"
    , ""
""
};

static const int qtscript_QSslKey_function_lengths[] = {
    5
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QSslKey_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSslKey::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSslKey)
Q_DECLARE_METATYPE(QSslKey*)
Q_DECLARE_METATYPE(QSsl::KeyAlgorithm)
Q_DECLARE_METATYPE(Qt::HANDLE)
Q_DECLARE_METATYPE(QSsl::KeyType)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QSsl::EncodingFormat)

//
// QSslKey
//

static QScriptValue qtscript_QSslKey_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSslKey* _q_self = qscriptvalue_cast<QSslKey*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSslKey.%0(): this object is not a QSslKey")
            .arg(qtscript_QSslKey_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSsl::KeyAlgorithm _q_result = _q_self->algorithm();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        Qt::HANDLE _q_result = _q_self->handle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QSslKey _q_arg0 = qscriptvalue_cast<QSslKey>(context->argument(0));
        QSslKey& _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QSslKey _q_arg0 = qscriptvalue_cast<QSslKey>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QSslKey _q_arg0 = qscriptvalue_cast<QSslKey>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toDer();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = _q_self->toDer(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toPem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = _q_self->toPem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QSsl::KeyType _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
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
    return qtscript_QSslKey_throw_ambiguity_error_helper(context,
        qtscript_QSslKey_function_names[_id+1],
        qtscript_QSslKey_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSslKey_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSslKey(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSslKey _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::HANDLE>() == context->argument(0).toVariant().userType())) {
            Qt::HANDLE _q_arg0 = qscriptvalue_cast<Qt::HANDLE>(context->argument(0));
            QSslKey _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QSslKey>() == context->argument(0).toVariant().userType())) {
            QSslKey _q_arg0 = qscriptvalue_cast<QSslKey>(context->argument(0));
            QSslKey _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<Qt::HANDLE>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyType>() == context->argument(1).toVariant().userType())) {
            Qt::HANDLE _q_arg0 = qscriptvalue_cast<Qt::HANDLE>(context->argument(0));
            QSsl::KeyType _q_arg1 = qscriptvalue_cast<QSsl::KeyType>(context->argument(1));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(2).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(2).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyType>() == context->argument(3).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
            QSsl::KeyType _q_arg3 = qscriptvalue_cast<QSsl::KeyType>(context->argument(3));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyType>() == context->argument(3).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
            QSsl::KeyType _q_arg3 = qscriptvalue_cast<QSsl::KeyType>(context->argument(3));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyType>() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(4).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
            QSsl::KeyType _q_arg3 = qscriptvalue_cast<QSsl::KeyType>(context->argument(3));
            QByteArray _q_arg4 = qscriptvalue_cast<QByteArray>(context->argument(4));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyAlgorithm>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QSsl::KeyType>() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(4).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QSsl::KeyAlgorithm _q_arg1 = qscriptvalue_cast<QSsl::KeyAlgorithm>(context->argument(1));
            QSsl::EncodingFormat _q_arg2 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(2));
            QSsl::KeyType _q_arg3 = qscriptvalue_cast<QSsl::KeyType>(context->argument(3));
            QByteArray _q_arg4 = qscriptvalue_cast<QByteArray>(context->argument(4));
            QSslKey _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslKey_throw_ambiguity_error_helper(context,
        qtscript_QSslKey_function_names[_id],
        qtscript_QSslKey_function_signatures[_id]);
}

QScriptValue qtscript_create_QSslKey_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSslKey*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSslKey*)0));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslKey_prototype_call, qtscript_QSslKey_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSslKey_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSslKey>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSslKey*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSslKey_static_call, proto, qtscript_QSslKey_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
