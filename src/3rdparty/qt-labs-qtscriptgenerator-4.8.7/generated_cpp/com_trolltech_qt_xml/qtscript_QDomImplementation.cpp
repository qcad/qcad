#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdom.h>
#include <QVariant>
#include <qdom.h>

static const char * const qtscript_QDomImplementation_function_names[] = {
    "QDomImplementation"
    // static
    , "invalidDataPolicy"
    , "setInvalidDataPolicy"
    // prototype
    , "createDocument"
    , "createDocumentType"
    , "hasFeature"
    , "isNull"
    , "equals"
    , "toString"
};

static const char * const qtscript_QDomImplementation_function_signatures[] = {
    "\nQDomImplementation arg__1"
    // static
    , ""
    , "InvalidDataPolicy policy"
    // prototype
    , "String nsURI, String qName, QDomDocumentType doctype"
    , "String qName, String publicId, String systemId"
    , "String feature, String version"
    , ""
    , "QDomImplementation arg__1"
""
};

static const int qtscript_QDomImplementation_function_lengths[] = {
    1
    // static
    , 0
    , 1
    // prototype
    , 3
    , 3
    , 2
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QDomImplementation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomImplementation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomImplementation)
Q_DECLARE_METATYPE(QDomImplementation*)
Q_DECLARE_METATYPE(QDomImplementation::InvalidDataPolicy)
Q_DECLARE_METATYPE(QDomDocumentType)
Q_DECLARE_METATYPE(QDomDocument)

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
// QDomImplementation::InvalidDataPolicy
//

static const QDomImplementation::InvalidDataPolicy qtscript_QDomImplementation_InvalidDataPolicy_values[] = {
    QDomImplementation::AcceptInvalidChars
    , QDomImplementation::DropInvalidChars
    , QDomImplementation::ReturnNullNode
};

static const char * const qtscript_QDomImplementation_InvalidDataPolicy_keys[] = {
    "AcceptInvalidChars"
    , "DropInvalidChars"
    , "ReturnNullNode"
};

static QString qtscript_QDomImplementation_InvalidDataPolicy_toStringHelper(QDomImplementation::InvalidDataPolicy value)
{
    if ((value >= QDomImplementation::AcceptInvalidChars) && (value <= QDomImplementation::ReturnNullNode))
        return qtscript_QDomImplementation_InvalidDataPolicy_keys[static_cast<int>(value)-static_cast<int>(QDomImplementation::AcceptInvalidChars)];
    return QString();
}

static QScriptValue qtscript_QDomImplementation_InvalidDataPolicy_toScriptValue(QScriptEngine *engine, const QDomImplementation::InvalidDataPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDomImplementation"));
    return clazz.property(qtscript_QDomImplementation_InvalidDataPolicy_toStringHelper(value));
}

static void qtscript_QDomImplementation_InvalidDataPolicy_fromScriptValue(const QScriptValue &value, QDomImplementation::InvalidDataPolicy &out)
{
    out = qvariant_cast<QDomImplementation::InvalidDataPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QDomImplementation_InvalidDataPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDomImplementation::AcceptInvalidChars) && (arg <= QDomImplementation::ReturnNullNode))
        return qScriptValueFromValue(engine,  static_cast<QDomImplementation::InvalidDataPolicy>(arg));
    return context->throwError(QString::fromLatin1("InvalidDataPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDomImplementation_InvalidDataPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDomImplementation::InvalidDataPolicy value = qscriptvalue_cast<QDomImplementation::InvalidDataPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDomImplementation_InvalidDataPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDomImplementation::InvalidDataPolicy value = qscriptvalue_cast<QDomImplementation::InvalidDataPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QDomImplementation_InvalidDataPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QDomImplementation_InvalidDataPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDomImplementation_InvalidDataPolicy,
        qtscript_QDomImplementation_InvalidDataPolicy_valueOf, qtscript_QDomImplementation_InvalidDataPolicy_toString);
    qScriptRegisterMetaType<QDomImplementation::InvalidDataPolicy>(engine, qtscript_QDomImplementation_InvalidDataPolicy_toScriptValue,
        qtscript_QDomImplementation_InvalidDataPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDomImplementation_InvalidDataPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDomImplementation_InvalidDataPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDomImplementation
//

static QScriptValue qtscript_QDomImplementation_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDomImplementation* _q_self = qscriptvalue_cast<QDomImplementation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomImplementation.%0(): this object is not a QDomImplementation")
            .arg(qtscript_QDomImplementation_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDomDocumentType _q_arg2 = qscriptvalue_cast<QDomDocumentType>(context->argument(2));
        QDomDocument _q_result = _q_self->createDocument(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QDomDocumentType _q_result = _q_self->createDocumentType(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->hasFeature(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QDomImplementation _q_arg0 = qscriptvalue_cast<QDomImplementation>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QDomImplementation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomImplementation_throw_ambiguity_error_helper(context,
        qtscript_QDomImplementation_function_names[_id+3],
        qtscript_QDomImplementation_function_signatures[_id+3]);
}

static QScriptValue qtscript_QDomImplementation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomImplementation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomImplementation _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomImplementation _q_arg0 = qscriptvalue_cast<QDomImplementation>(context->argument(0));
        QDomImplementation _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QDomImplementation::InvalidDataPolicy _q_result = QDomImplementation::invalidDataPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QDomImplementation::InvalidDataPolicy _q_arg0 = qscriptvalue_cast<QDomImplementation::InvalidDataPolicy>(context->argument(0));
        QDomImplementation::setInvalidDataPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomImplementation_throw_ambiguity_error_helper(context,
        qtscript_QDomImplementation_function_names[_id],
        qtscript_QDomImplementation_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomImplementation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomImplementation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomImplementation*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomImplementation_prototype_call, qtscript_QDomImplementation_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomImplementation_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomImplementation>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomImplementation*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomImplementation_static_call, proto, qtscript_QDomImplementation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomImplementation_static_call,
            qtscript_QDomImplementation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QDomImplementation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("InvalidDataPolicy"),
        qtscript_create_QDomImplementation_InvalidDataPolicy_class(engine, ctor));
    return ctor;
}
