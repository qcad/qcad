#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsocketnotifier.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsocketnotifier.h>

static const char * const qtscript_QSocketNotifier_function_names[] = {
    "QSocketNotifier"
    // static
    // prototype
    , "isEnabled"
    , "type"
    , "toString"
};

static const char * const qtscript_QSocketNotifier_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QSocketNotifier_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSocketNotifier_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSocketNotifier::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSocketNotifier*)
Q_DECLARE_METATYPE(QSocketNotifier::Type)

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
// QSocketNotifier::Type
//

static const QSocketNotifier::Type qtscript_QSocketNotifier_Type_values[] = {
    QSocketNotifier::Read
    , QSocketNotifier::Write
    , QSocketNotifier::Exception
};

static const char * const qtscript_QSocketNotifier_Type_keys[] = {
    "Read"
    , "Write"
    , "Exception"
};

static QString qtscript_QSocketNotifier_Type_toStringHelper(QSocketNotifier::Type value)
{
    if ((value >= QSocketNotifier::Read) && (value <= QSocketNotifier::Exception))
        return qtscript_QSocketNotifier_Type_keys[static_cast<int>(value)-static_cast<int>(QSocketNotifier::Read)];
    return QString();
}

static QScriptValue qtscript_QSocketNotifier_Type_toScriptValue(QScriptEngine *engine, const QSocketNotifier::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSocketNotifier"));
    return clazz.property(qtscript_QSocketNotifier_Type_toStringHelper(value));
}

static void qtscript_QSocketNotifier_Type_fromScriptValue(const QScriptValue &value, QSocketNotifier::Type &out)
{
    out = qvariant_cast<QSocketNotifier::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_QSocketNotifier_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSocketNotifier::Read) && (arg <= QSocketNotifier::Exception))
        return qScriptValueFromValue(engine,  static_cast<QSocketNotifier::Type>(arg));
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSocketNotifier_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSocketNotifier::Type value = qscriptvalue_cast<QSocketNotifier::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSocketNotifier_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSocketNotifier::Type value = qscriptvalue_cast<QSocketNotifier::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_QSocketNotifier_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_QSocketNotifier_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSocketNotifier_Type,
        qtscript_QSocketNotifier_Type_valueOf, qtscript_QSocketNotifier_Type_toString);
    qScriptRegisterMetaType<QSocketNotifier::Type>(engine, qtscript_QSocketNotifier_Type_toScriptValue,
        qtscript_QSocketNotifier_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSocketNotifier_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSocketNotifier_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSocketNotifier
//

static QScriptValue qtscript_QSocketNotifier_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSocketNotifier* _q_self = qscriptvalue_cast<QSocketNotifier*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSocketNotifier.%0(): this object is not a QSocketNotifier")
            .arg(qtscript_QSocketNotifier_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSocketNotifier::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QSocketNotifier");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSocketNotifier_throw_ambiguity_error_helper(context,
        qtscript_QSocketNotifier_function_names[_id+1],
        qtscript_QSocketNotifier_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSocketNotifier_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QSocketNotifier cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSocketNotifier_throw_ambiguity_error_helper(context,
        qtscript_QSocketNotifier_function_names[_id],
        qtscript_QSocketNotifier_function_signatures[_id]);
}

static QScriptValue qtscript_QSocketNotifier_toScriptValue(QScriptEngine *engine, QSocketNotifier* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSocketNotifier_fromScriptValue(const QScriptValue &value, QSocketNotifier* &out)
{
    out = qobject_cast<QSocketNotifier*>(value.toQObject());
}

QScriptValue qtscript_create_QSocketNotifier_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSocketNotifier*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSocketNotifier*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSocketNotifier_prototype_call, qtscript_QSocketNotifier_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSocketNotifier_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSocketNotifier*>(engine, qtscript_QSocketNotifier_toScriptValue, 
        qtscript_QSocketNotifier_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSocketNotifier_static_call, proto, qtscript_QSocketNotifier_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_QSocketNotifier_Type_class(engine, ctor));
    return ctor;
}
