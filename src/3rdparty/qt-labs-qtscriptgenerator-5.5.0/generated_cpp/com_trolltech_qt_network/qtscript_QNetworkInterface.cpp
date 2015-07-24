#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qnetworkinterface.h>
#include <QVariant>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkinterface.h>

static const char * const qtscript_QNetworkInterface_function_names[] = {
    "QNetworkInterface"
    // static
    , "allAddresses"
    , "allInterfaces"
    , "interfaceFromIndex"
    , "interfaceFromName"
    // prototype
    , "addressEntries"
    , "flags"
    , "hardwareAddress"
    , "humanReadableName"
    , "index"
    , "isValid"
    , "name"
    , "swap"
    , "toString"
};

static const char * const qtscript_QNetworkInterface_function_signatures[] = {
    "\nQNetworkInterface other"
    // static
    , ""
    , ""
    , "int index"
    , "String name"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QNetworkInterface other"
""
};

static const int qtscript_QNetworkInterface_function_lengths[] = {
    1
    // static
    , 0
    , 0
    , 1
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QNetworkInterface_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkInterface::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkInterface)
Q_DECLARE_METATYPE(QNetworkInterface*)
Q_DECLARE_METATYPE(QNetworkInterface::InterfaceFlag)
Q_DECLARE_METATYPE(QFlags<QNetworkInterface::InterfaceFlag>)
Q_DECLARE_METATYPE(QNetworkAddressEntry)
Q_DECLARE_METATYPE(QList<QNetworkAddressEntry >)
Q_DECLARE_METATYPE(QHostAddress)
Q_DECLARE_METATYPE(QList<QHostAddress >)
Q_DECLARE_METATYPE(QList<QNetworkInterface >)

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
// QNetworkInterface::InterfaceFlag
//

static const QNetworkInterface::InterfaceFlag qtscript_QNetworkInterface_InterfaceFlag_values[] = {
    QNetworkInterface::IsUp
    , QNetworkInterface::IsRunning
    , QNetworkInterface::CanBroadcast
    , QNetworkInterface::IsLoopBack
    , QNetworkInterface::IsPointToPoint
    , QNetworkInterface::CanMulticast
};

static const char * const qtscript_QNetworkInterface_InterfaceFlag_keys[] = {
    "IsUp"
    , "IsRunning"
    , "CanBroadcast"
    , "IsLoopBack"
    , "IsPointToPoint"
    , "CanMulticast"
};

static QString qtscript_QNetworkInterface_InterfaceFlag_toStringHelper(QNetworkInterface::InterfaceFlag value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QNetworkInterface_InterfaceFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QNetworkInterface_InterfaceFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QNetworkInterface_InterfaceFlag_toScriptValue(QScriptEngine *engine, const QNetworkInterface::InterfaceFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkInterface"));
    return clazz.property(qtscript_QNetworkInterface_InterfaceFlag_toStringHelper(value));
}

static void qtscript_QNetworkInterface_InterfaceFlag_fromScriptValue(const QScriptValue &value, QNetworkInterface::InterfaceFlag &out)
{
    out = qvariant_cast<QNetworkInterface::InterfaceFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkInterface_InterfaceFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QNetworkInterface_InterfaceFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QNetworkInterface::InterfaceFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("InterfaceFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkInterface_InterfaceFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkInterface::InterfaceFlag value = qscriptvalue_cast<QNetworkInterface::InterfaceFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkInterface_InterfaceFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkInterface::InterfaceFlag value = qscriptvalue_cast<QNetworkInterface::InterfaceFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkInterface_InterfaceFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkInterface_InterfaceFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkInterface_InterfaceFlag,
        qtscript_QNetworkInterface_InterfaceFlag_valueOf, qtscript_QNetworkInterface_InterfaceFlag_toString);
    qScriptRegisterMetaType<QNetworkInterface::InterfaceFlag>(engine, qtscript_QNetworkInterface_InterfaceFlag_toScriptValue,
        qtscript_QNetworkInterface_InterfaceFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkInterface_InterfaceFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkInterface_InterfaceFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkInterface::InterfaceFlags
//

static QScriptValue qtscript_QNetworkInterface_InterfaceFlags_toScriptValue(QScriptEngine *engine, const QNetworkInterface::InterfaceFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QNetworkInterface_InterfaceFlags_fromScriptValue(const QScriptValue &value, QNetworkInterface::InterfaceFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QNetworkInterface::InterfaceFlags>())
        out = qvariant_cast<QNetworkInterface::InterfaceFlags>(var);
    else if (var.userType() == qMetaTypeId<QNetworkInterface::InterfaceFlag>())
        out = qvariant_cast<QNetworkInterface::InterfaceFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QNetworkInterface_InterfaceFlags(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkInterface::InterfaceFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QNetworkInterface::InterfaceFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QNetworkInterface::InterfaceFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("InterfaceFlags(): argument %0 is not of type InterfaceFlag").arg(i));
            }
            result |= qvariant_cast<QNetworkInterface::InterfaceFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QNetworkInterface_InterfaceFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkInterface::InterfaceFlags value = qscriptvalue_cast<QNetworkInterface::InterfaceFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkInterface_InterfaceFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkInterface::InterfaceFlags value = qscriptvalue_cast<QNetworkInterface::InterfaceFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_QNetworkInterface_InterfaceFlag_values[i]) == qtscript_QNetworkInterface_InterfaceFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QNetworkInterface_InterfaceFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QNetworkInterface_InterfaceFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QNetworkInterface::InterfaceFlags>() == otherObj.value<QNetworkInterface::InterfaceFlags>())));
}

static QScriptValue qtscript_create_QNetworkInterface_InterfaceFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QNetworkInterface_InterfaceFlags, qtscript_QNetworkInterface_InterfaceFlags_valueOf,
        qtscript_QNetworkInterface_InterfaceFlags_toString, qtscript_QNetworkInterface_InterfaceFlags_equals);
    qScriptRegisterMetaType<QNetworkInterface::InterfaceFlags>(engine, qtscript_QNetworkInterface_InterfaceFlags_toScriptValue,
        qtscript_QNetworkInterface_InterfaceFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QNetworkInterface
//

static QScriptValue qtscript_QNetworkInterface_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QNetworkInterface* _q_self = qscriptvalue_cast<QNetworkInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkInterface.%0(): this object is not a QNetworkInterface")
            .arg(qtscript_QNetworkInterface_function_names[_id+5]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QNetworkAddressEntry > _q_result = _q_self->addressEntries();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFlags<QNetworkInterface::InterfaceFlag> _q_result = _q_self->flags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->hardwareAddress();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->humanReadableName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->index();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QNetworkInterface _q_arg0 = qscriptvalue_cast<QNetworkInterface>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkInterface_throw_ambiguity_error_helper(context,
        qtscript_QNetworkInterface_function_names[_id+5],
        qtscript_QNetworkInterface_function_signatures[_id+5]);
}

static QScriptValue qtscript_QNetworkInterface_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkInterface(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QNetworkInterface _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QNetworkInterface _q_arg0 = qscriptvalue_cast<QNetworkInterface>(context->argument(0));
        QNetworkInterface _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QHostAddress > _q_result = QNetworkInterface::allAddresses();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QNetworkInterface > _q_result = QNetworkInterface::allInterfaces();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QNetworkInterface _q_result = QNetworkInterface::interfaceFromIndex(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QNetworkInterface _q_result = QNetworkInterface::interfaceFromName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkInterface_throw_ambiguity_error_helper(context,
        qtscript_QNetworkInterface_function_names[_id],
        qtscript_QNetworkInterface_function_signatures[_id]);
}

QScriptValue qtscript_create_QNetworkInterface_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkInterface*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkInterface_prototype_call, qtscript_QNetworkInterface_function_lengths[i+5]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkInterface_function_names[i+5]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QNetworkInterface>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QNetworkInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkInterface_static_call, proto, qtscript_QNetworkInterface_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkInterface_static_call,
            qtscript_QNetworkInterface_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QNetworkInterface_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("InterfaceFlag"),
        qtscript_create_QNetworkInterface_InterfaceFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("InterfaceFlags"),
        qtscript_create_QNetworkInterface_InterfaceFlags_class(engine));
    return ctor;
}
