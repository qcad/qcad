#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <QVariant>

#include <qglobal.h>

class Global {};

static const char * const qtscript_Global_function_names[] = {
    "Global"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_Global_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_Global_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_Global_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("Global::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Global*)
Q_DECLARE_METATYPE(QtMsgType)

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
// QtMsgType
//

static const QtMsgType qtscript_Global_QtMsgType_values[] = {
    QtDebugMsg
    , QtWarningMsg
    , QtCriticalMsg
    , QtFatalMsg
};

static const char * const qtscript_Global_QtMsgType_keys[] = {
    "QtDebugMsg"
    , "QtWarningMsg"
    , "QtCriticalMsg"
    , "QtFatalMsg"
};

static QString qtscript_Global_QtMsgType_toStringHelper(QtMsgType value)
{
    if ((value >= QtDebugMsg) && (value <= QtFatalMsg))
        return qtscript_Global_QtMsgType_keys[static_cast<int>(value)-static_cast<int>(QtDebugMsg)];
    return QString();
}

static QScriptValue qtscript_Global_QtMsgType_toScriptValue(QScriptEngine *engine, const QtMsgType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Global"));
    return clazz.property(qtscript_Global_QtMsgType_toStringHelper(value));
}

static void qtscript_Global_QtMsgType_fromScriptValue(const QScriptValue &value, QtMsgType &out)
{
    out = qvariant_cast<QtMsgType>(value.toVariant());
}

static QScriptValue qtscript_construct_Global_QtMsgType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QtDebugMsg) && (arg <= QtFatalMsg))
        return qScriptValueFromValue(engine,  static_cast<QtMsgType>(arg));
    return context->throwError(QString::fromLatin1("QtMsgType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Global_QtMsgType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QtMsgType value = qscriptvalue_cast<QtMsgType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Global_QtMsgType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QtMsgType value = qscriptvalue_cast<QtMsgType>(context->thisObject());
    return QScriptValue(engine, qtscript_Global_QtMsgType_toStringHelper(value));
}

static QScriptValue qtscript_create_Global_QtMsgType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Global_QtMsgType,
        qtscript_Global_QtMsgType_valueOf, qtscript_Global_QtMsgType_toString);
    qScriptRegisterMetaType<QtMsgType>(engine, qtscript_Global_QtMsgType_toScriptValue,
        qtscript_Global_QtMsgType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Global_QtMsgType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Global_QtMsgType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Global
//

static QScriptValue qtscript_Global_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Global* _q_self = qscriptvalue_cast<Global*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("Global.%0(): this object is not a Global")
            .arg(qtscript_Global_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("Global");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_Global_throw_ambiguity_error_helper(context,
        qtscript_Global_function_names[_id+1],
        qtscript_Global_function_signatures[_id+1]);
}

static QScriptValue qtscript_Global_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("Global cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_Global_throw_ambiguity_error_helper(context,
        qtscript_Global_function_names[_id],
        qtscript_Global_function_signatures[_id]);
}

QScriptValue qtscript_create_Global_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Global*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Global*)0));

    engine->setDefaultPrototype(qMetaTypeId<Global*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_Global_static_call, proto, qtscript_Global_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("QtMsgType"),
        qtscript_create_Global_QtMsgType_class(engine, ctor));
    return ctor;
}
