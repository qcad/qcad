#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsqlerror.h>
#include <QVariant>
#include <qsqlerror.h>

static const char * const qtscript_QSqlError_function_names[] = {
    "QSqlError"
    // static
    // prototype
    , "databaseText"
    , "driverText"
    , "isValid"
    , "nativeErrorCode"
    , "number"
    , "equals"
    , "setDatabaseText"
    , "setDriverText"
    , "setNumber"
    , "setType"
    , "text"
    , "type"
    , "toString"
};

static const char * const qtscript_QSqlError_function_signatures[] = {
    "QSqlError other\nString driverText, String databaseText, ErrorType type, String errorCode\nString driverText, String databaseText, ErrorType type, int number"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QSqlError other"
    , "String databaseText"
    , "String driverText"
    , "int number"
    , "ErrorType type"
    , ""
    , ""
""
};

static const int qtscript_QSqlError_function_lengths[] = {
    4
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
    , 0
};

static QScriptValue qtscript_QSqlError_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlError::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlError)
Q_DECLARE_METATYPE(QSqlError*)
Q_DECLARE_METATYPE(QSqlError::ErrorType)

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
// QSqlError::ErrorType
//

static const QSqlError::ErrorType qtscript_QSqlError_ErrorType_values[] = {
    QSqlError::NoError
    , QSqlError::ConnectionError
    , QSqlError::StatementError
    , QSqlError::TransactionError
    , QSqlError::UnknownError
};

static const char * const qtscript_QSqlError_ErrorType_keys[] = {
    "NoError"
    , "ConnectionError"
    , "StatementError"
    , "TransactionError"
    , "UnknownError"
};

static QString qtscript_QSqlError_ErrorType_toStringHelper(QSqlError::ErrorType value)
{
    if ((value >= QSqlError::NoError) && (value <= QSqlError::UnknownError))
        return qtscript_QSqlError_ErrorType_keys[static_cast<int>(value)-static_cast<int>(QSqlError::NoError)];
    return QString();
}

static QScriptValue qtscript_QSqlError_ErrorType_toScriptValue(QScriptEngine *engine, const QSqlError::ErrorType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlError"));
    return clazz.property(qtscript_QSqlError_ErrorType_toStringHelper(value));
}

static void qtscript_QSqlError_ErrorType_fromScriptValue(const QScriptValue &value, QSqlError::ErrorType &out)
{
    out = qvariant_cast<QSqlError::ErrorType>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlError_ErrorType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlError::NoError) && (arg <= QSqlError::UnknownError))
        return qScriptValueFromValue(engine,  static_cast<QSqlError::ErrorType>(arg));
    return context->throwError(QString::fromLatin1("ErrorType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlError_ErrorType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlError::ErrorType value = qscriptvalue_cast<QSqlError::ErrorType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlError_ErrorType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlError::ErrorType value = qscriptvalue_cast<QSqlError::ErrorType>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlError_ErrorType_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlError_ErrorType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlError_ErrorType,
        qtscript_QSqlError_ErrorType_valueOf, qtscript_QSqlError_ErrorType_toString);
    qScriptRegisterMetaType<QSqlError::ErrorType>(engine, qtscript_QSqlError_ErrorType_toScriptValue,
        qtscript_QSqlError_ErrorType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlError_ErrorType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlError_ErrorType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlError
//

static QScriptValue qtscript_QSqlError_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlError* _q_self = qscriptvalue_cast<QSqlError*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlError.%0(): this object is not a QSqlError")
            .arg(qtscript_QSqlError_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->databaseText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->driverText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->nativeErrorCode();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->number();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QSqlError _q_arg0 = qscriptvalue_cast<QSqlError>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setDatabaseText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setDriverText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setNumber(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QSqlError::ErrorType _q_arg0 = qscriptvalue_cast<QSqlError::ErrorType>(context->argument(0));
        _q_self->setType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QSqlError::ErrorType _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlError_throw_ambiguity_error_helper(context,
        qtscript_QSqlError_function_names[_id+1],
        qtscript_QSqlError_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlError_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlError(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSqlError _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSqlError>() == context->argument(0).toVariant().userType())) {
            QSqlError _q_arg0 = qscriptvalue_cast<QSqlError>(context->argument(0));
            QSqlError _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QSqlError _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QSqlError _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QSqlError::ErrorType _q_arg2 = qscriptvalue_cast<QSqlError::ErrorType>(context->argument(2));
        QSqlError _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        if (context->argument(0).isString()
            && context->argument(1).isString()
            && (qMetaTypeId<QSqlError::ErrorType>() == context->argument(2).toVariant().userType())
            && context->argument(3).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QSqlError::ErrorType _q_arg2 = qscriptvalue_cast<QSqlError::ErrorType>(context->argument(2));
            QString _q_arg3 = context->argument(3).toString();
            QSqlError _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && (qMetaTypeId<QSqlError::ErrorType>() == context->argument(2).toVariant().userType())
            && context->argument(3).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QSqlError::ErrorType _q_arg2 = qscriptvalue_cast<QSqlError::ErrorType>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            QSqlError _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlError_throw_ambiguity_error_helper(context,
        qtscript_QSqlError_function_names[_id],
        qtscript_QSqlError_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlError_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlError*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlError*)0));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlError_prototype_call, qtscript_QSqlError_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlError_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlError>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSqlError*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlError_static_call, proto, qtscript_QSqlError_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ErrorType"),
        qtscript_create_QSqlError_ErrorType_class(engine, ctor));
    return ctor;
}
