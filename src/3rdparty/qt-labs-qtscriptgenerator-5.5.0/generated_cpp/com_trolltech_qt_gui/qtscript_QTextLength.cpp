#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextformat.h>
#include <QVariant>
#include <qtextformat.h>

static const char * const qtscript_QTextLength_function_names[] = {
    "QTextLength"
    // static
    // prototype
    , "equals"
    , "rawValue"
    , "type"
    , "value"
    , "toString"
};

static const char * const qtscript_QTextLength_function_signatures[] = {
    "\nType type, qreal value"
    // static
    // prototype
    , "QTextLength other"
    , ""
    , ""
    , "qreal maximumLength"
""
};

static const int qtscript_QTextLength_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTextLength_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextLength::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextLength*)
Q_DECLARE_METATYPE(QTextLength::Type)

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
// QTextLength::Type
//

static const QTextLength::Type qtscript_QTextLength_Type_values[] = {
    QTextLength::VariableLength
    , QTextLength::FixedLength
    , QTextLength::PercentageLength
};

static const char * const qtscript_QTextLength_Type_keys[] = {
    "VariableLength"
    , "FixedLength"
    , "PercentageLength"
};

static QString qtscript_QTextLength_Type_toStringHelper(QTextLength::Type value)
{
    if ((value >= QTextLength::VariableLength) && (value <= QTextLength::PercentageLength))
        return qtscript_QTextLength_Type_keys[static_cast<int>(value)-static_cast<int>(QTextLength::VariableLength)];
    return QString();
}

static QScriptValue qtscript_QTextLength_Type_toScriptValue(QScriptEngine *engine, const QTextLength::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextLength"));
    return clazz.property(qtscript_QTextLength_Type_toStringHelper(value));
}

static void qtscript_QTextLength_Type_fromScriptValue(const QScriptValue &value, QTextLength::Type &out)
{
    out = qvariant_cast<QTextLength::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextLength_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextLength::VariableLength) && (arg <= QTextLength::PercentageLength))
        return qScriptValueFromValue(engine,  static_cast<QTextLength::Type>(arg));
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextLength_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextLength::Type value = qscriptvalue_cast<QTextLength::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextLength_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextLength::Type value = qscriptvalue_cast<QTextLength::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextLength_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextLength_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextLength_Type,
        qtscript_QTextLength_Type_valueOf, qtscript_QTextLength_Type_toString);
    qScriptRegisterMetaType<QTextLength::Type>(engine, qtscript_QTextLength_Type_toScriptValue,
        qtscript_QTextLength_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextLength_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextLength_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextLength
//

static QScriptValue qtscript_QTextLength_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextLength* _q_self = qscriptvalue_cast<QTextLength*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextLength.%0(): this object is not a QTextLength")
            .arg(qtscript_QTextLength_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QTextLength _q_arg0 = qscriptvalue_cast<QTextLength>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->rawValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTextLength::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->value(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextLength_throw_ambiguity_error_helper(context,
        qtscript_QTextLength_function_names[_id+1],
        qtscript_QTextLength_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextLength_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextLength(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextLength _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QTextLength::Type _q_arg0 = qscriptvalue_cast<QTextLength::Type>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QTextLength _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextLength_throw_ambiguity_error_helper(context,
        qtscript_QTextLength_function_names[_id],
        qtscript_QTextLength_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextLength_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextLength*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextLength*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextLength_prototype_call, qtscript_QTextLength_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextLength_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextLength>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextLength*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextLength_static_call, proto, qtscript_QTextLength_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_QTextLength_Type_class(engine, ctor));
    return ctor;
}
