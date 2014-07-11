#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsessionmanager.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

static const char * const qtscript_QSessionManager_function_names[] = {
    "QSessionManager"
    // static
    // prototype
    , "allowsErrorInteraction"
    , "allowsInteraction"
    , "cancel"
    , "discardCommand"
    , "isPhase2"
    , "release"
    , "requestPhase2"
    , "restartCommand"
    , "restartHint"
    , "sessionId"
    , "sessionKey"
    , "setDiscardCommand"
    , "setManagerProperty"
    , "setRestartCommand"
    , "setRestartHint"
    , "toString"
};

static const char * const qtscript_QSessionManager_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "List arg__1"
    , "String name, String value\nString name, List value"
    , "List arg__1"
    , "RestartHint arg__1"
""
};

static const int qtscript_QSessionManager_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QSessionManager_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSessionManager::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSessionManager*)
Q_DECLARE_METATYPE(QSessionManager::RestartHint)

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
// QSessionManager::RestartHint
//

static const QSessionManager::RestartHint qtscript_QSessionManager_RestartHint_values[] = {
    QSessionManager::RestartIfRunning
    , QSessionManager::RestartAnyway
    , QSessionManager::RestartImmediately
    , QSessionManager::RestartNever
};

static const char * const qtscript_QSessionManager_RestartHint_keys[] = {
    "RestartIfRunning"
    , "RestartAnyway"
    , "RestartImmediately"
    , "RestartNever"
};

static QString qtscript_QSessionManager_RestartHint_toStringHelper(QSessionManager::RestartHint value)
{
    if ((value >= QSessionManager::RestartIfRunning) && (value <= QSessionManager::RestartNever))
        return qtscript_QSessionManager_RestartHint_keys[static_cast<int>(value)-static_cast<int>(QSessionManager::RestartIfRunning)];
    return QString();
}

static QScriptValue qtscript_QSessionManager_RestartHint_toScriptValue(QScriptEngine *engine, const QSessionManager::RestartHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSessionManager"));
    return clazz.property(qtscript_QSessionManager_RestartHint_toStringHelper(value));
}

static void qtscript_QSessionManager_RestartHint_fromScriptValue(const QScriptValue &value, QSessionManager::RestartHint &out)
{
    out = qvariant_cast<QSessionManager::RestartHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QSessionManager_RestartHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSessionManager::RestartIfRunning) && (arg <= QSessionManager::RestartNever))
        return qScriptValueFromValue(engine,  static_cast<QSessionManager::RestartHint>(arg));
    return context->throwError(QString::fromLatin1("RestartHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSessionManager_RestartHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSessionManager::RestartHint value = qscriptvalue_cast<QSessionManager::RestartHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSessionManager_RestartHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSessionManager::RestartHint value = qscriptvalue_cast<QSessionManager::RestartHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QSessionManager_RestartHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QSessionManager_RestartHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSessionManager_RestartHint,
        qtscript_QSessionManager_RestartHint_valueOf, qtscript_QSessionManager_RestartHint_toString);
    qScriptRegisterMetaType<QSessionManager::RestartHint>(engine, qtscript_QSessionManager_RestartHint_toScriptValue,
        qtscript_QSessionManager_RestartHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSessionManager_RestartHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSessionManager_RestartHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSessionManager
//

static QScriptValue qtscript_QSessionManager_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 15;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSessionManager* _q_self = qscriptvalue_cast<QSessionManager*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSessionManager.%0(): this object is not a QSessionManager")
            .arg(qtscript_QSessionManager_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->allowsErrorInteraction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->allowsInteraction();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->cancel();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->discardCommand();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isPhase2();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->release();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->requestPhase2();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->restartCommand();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QSessionManager::RestartHint _q_result = _q_self->restartHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->sessionId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->sessionKey();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setDiscardCommand(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            _q_self->setManagerProperty(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isArray()) {
            QString _q_arg0 = context->argument(0).toString();
            QStringList _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            _q_self->setManagerProperty(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setRestartCommand(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QSessionManager::RestartHint _q_arg0 = qscriptvalue_cast<QSessionManager::RestartHint>(context->argument(0));
        _q_self->setRestartHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15: {
    QString result = QString::fromLatin1("QSessionManager");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSessionManager_throw_ambiguity_error_helper(context,
        qtscript_QSessionManager_function_names[_id+1],
        qtscript_QSessionManager_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSessionManager_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QSessionManager cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSessionManager_throw_ambiguity_error_helper(context,
        qtscript_QSessionManager_function_names[_id],
        qtscript_QSessionManager_function_signatures[_id]);
}

static QScriptValue qtscript_QSessionManager_toScriptValue(QScriptEngine *engine, QSessionManager* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSessionManager_fromScriptValue(const QScriptValue &value, QSessionManager* &out)
{
    out = qobject_cast<QSessionManager*>(value.toQObject());
}

QScriptValue qtscript_create_QSessionManager_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSessionManager*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSessionManager*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 16; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSessionManager_prototype_call, qtscript_QSessionManager_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSessionManager_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSessionManager*>(engine, qtscript_QSessionManager_toScriptValue, 
        qtscript_QSessionManager_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSessionManager_static_call, proto, qtscript_QSessionManager_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("RestartHint"),
        qtscript_create_QSessionManager_RestartHint_class(engine, ctor));
    return ctor;
}
