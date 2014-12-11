#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qauthenticator.h>
#include <QVariant>
#include <qauthenticator.h>

static const char * const qtscript_QAuthenticator_function_names[] = {
    "QAuthenticator"
    // static
    // prototype
    , "isNull"
    , "equals"
    , "option"
    , "options"
    , "password"
    , "realm"
    , "setOption"
    , "setPassword"
    , "setUser"
    , "user"
    , "toString"
};

static const char * const qtscript_QAuthenticator_function_signatures[] = {
    "\nQAuthenticator other"
    // static
    // prototype
    , ""
    , "QAuthenticator other"
    , "String opt"
    , ""
    , ""
    , ""
    , "String opt, Object value"
    , "String password"
    , "String user"
    , ""
""
};

static const int qtscript_QAuthenticator_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QAuthenticator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAuthenticator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAuthenticator)
Q_DECLARE_METATYPE(QAuthenticator*)

//
// QAuthenticator
//

static QScriptValue qtscript_QAuthenticator_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAuthenticator* _q_self = qscriptvalue_cast<QAuthenticator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAuthenticator.%0(): this object is not a QAuthenticator")
            .arg(qtscript_QAuthenticator_function_names[_id+1]));
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
        QAuthenticator _q_arg0 = qscriptvalue_cast<QAuthenticator>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_result = _q_self->option(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QHash<QString,QVariant > _q_result = _q_self->options();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->password();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->realm();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPassword(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setUser(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->user();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QAuthenticator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAuthenticator_throw_ambiguity_error_helper(context,
        qtscript_QAuthenticator_function_names[_id+1],
        qtscript_QAuthenticator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAuthenticator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAuthenticator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QAuthenticator _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QAuthenticator _q_arg0 = qscriptvalue_cast<QAuthenticator>(context->argument(0));
        QAuthenticator _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAuthenticator_throw_ambiguity_error_helper(context,
        qtscript_QAuthenticator_function_names[_id],
        qtscript_QAuthenticator_function_signatures[_id]);
}

QScriptValue qtscript_create_QAuthenticator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAuthenticator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAuthenticator*)0));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAuthenticator_prototype_call, qtscript_QAuthenticator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAuthenticator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAuthenticator>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QAuthenticator*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAuthenticator_static_call, proto, qtscript_QAuthenticator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
