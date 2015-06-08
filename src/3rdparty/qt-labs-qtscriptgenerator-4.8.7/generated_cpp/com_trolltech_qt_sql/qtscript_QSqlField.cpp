#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsqlfield.h>
#include <QVariant>
#include <qsqlfield.h>

static const char * const qtscript_QSqlField_function_names[] = {
    "QSqlField"
    // static
    // prototype
    , "clear"
    , "defaultValue"
    , "isAutoValue"
    , "isGenerated"
    , "isNull"
    , "isReadOnly"
    , "isValid"
    , "length"
    , "name"
    , "equals"
    , "precision"
    , "requiredStatus"
    , "setAutoValue"
    , "setDefaultValue"
    , "setGenerated"
    , "setLength"
    , "setName"
    , "setPrecision"
    , "setReadOnly"
    , "setRequired"
    , "setRequiredStatus"
    , "setSqlType"
    , "setType"
    , "setValue"
    , "type"
    , "typeID"
    , "value"
    , "toString"
};

static const char * const qtscript_QSqlField_function_signatures[] = {
    "QSqlField other\nString fieldName, QVariant::Type type"
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
    , "QSqlField other"
    , ""
    , ""
    , "bool autoVal"
    , "Object value"
    , "bool gen"
    , "int fieldLength"
    , "String name"
    , "int precision"
    , "bool readOnly"
    , "bool required"
    , "RequiredStatus status"
    , "int type"
    , "QVariant::Type type"
    , "Object value"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QSqlField_function_lengths[] = {
    2
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
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSqlField_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlField::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlField)
Q_DECLARE_METATYPE(QSqlField*)
Q_DECLARE_METATYPE(QSqlField::RequiredStatus)
Q_DECLARE_METATYPE(QVariant::Type)

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
// QSqlField::RequiredStatus
//

static const QSqlField::RequiredStatus qtscript_QSqlField_RequiredStatus_values[] = {
    QSqlField::Unknown
    , QSqlField::Optional
    , QSqlField::Required
};

static const char * const qtscript_QSqlField_RequiredStatus_keys[] = {
    "Unknown"
    , "Optional"
    , "Required"
};

static QString qtscript_QSqlField_RequiredStatus_toStringHelper(QSqlField::RequiredStatus value)
{
    if ((value >= QSqlField::Unknown) && (value <= QSqlField::Required))
        return qtscript_QSqlField_RequiredStatus_keys[static_cast<int>(value)-static_cast<int>(QSqlField::Unknown)];
    return QString();
}

static QScriptValue qtscript_QSqlField_RequiredStatus_toScriptValue(QScriptEngine *engine, const QSqlField::RequiredStatus &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSqlField"));
    return clazz.property(qtscript_QSqlField_RequiredStatus_toStringHelper(value));
}

static void qtscript_QSqlField_RequiredStatus_fromScriptValue(const QScriptValue &value, QSqlField::RequiredStatus &out)
{
    out = qvariant_cast<QSqlField::RequiredStatus>(value.toVariant());
}

static QScriptValue qtscript_construct_QSqlField_RequiredStatus(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSqlField::Unknown) && (arg <= QSqlField::Required))
        return qScriptValueFromValue(engine,  static_cast<QSqlField::RequiredStatus>(arg));
    return context->throwError(QString::fromLatin1("RequiredStatus(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSqlField_RequiredStatus_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSqlField::RequiredStatus value = qscriptvalue_cast<QSqlField::RequiredStatus>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSqlField_RequiredStatus_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSqlField::RequiredStatus value = qscriptvalue_cast<QSqlField::RequiredStatus>(context->thisObject());
    return QScriptValue(engine, qtscript_QSqlField_RequiredStatus_toStringHelper(value));
}

static QScriptValue qtscript_create_QSqlField_RequiredStatus_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSqlField_RequiredStatus,
        qtscript_QSqlField_RequiredStatus_valueOf, qtscript_QSqlField_RequiredStatus_toString);
    qScriptRegisterMetaType<QSqlField::RequiredStatus>(engine, qtscript_QSqlField_RequiredStatus_toScriptValue,
        qtscript_QSqlField_RequiredStatus_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSqlField_RequiredStatus_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSqlField_RequiredStatus_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSqlField
//

static QScriptValue qtscript_QSqlField_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 27;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlField* _q_self = qscriptvalue_cast<QSqlField*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlField.%0(): this object is not a QSqlField")
            .arg(qtscript_QSqlField_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->defaultValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAutoValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isGenerated();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isReadOnly();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QSqlField _q_arg0 = qscriptvalue_cast<QSqlField>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->precision();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QSqlField::RequiredStatus _q_result = _q_self->requiredStatus();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAutoValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->setDefaultValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setGenerated(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLength(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPrecision(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setReadOnly(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setRequired(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QSqlField::RequiredStatus _q_arg0 = qscriptvalue_cast<QSqlField::RequiredStatus>(context->argument(0));
        _q_self->setRequiredStatus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setSqlType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QVariant::Type _q_arg0 = qscriptvalue_cast<QVariant::Type>(context->argument(0));
        _q_self->setType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->setValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QVariant::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->typeID();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->value();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlField_throw_ambiguity_error_helper(context,
        qtscript_QSqlField_function_names[_id+1],
        qtscript_QSqlField_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlField_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlField(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSqlField _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSqlField>() == context->argument(0).toVariant().userType())) {
            QSqlField _q_arg0 = qscriptvalue_cast<QSqlField>(context->argument(0));
            QSqlField _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QSqlField _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant::Type _q_arg1 = qscriptvalue_cast<QVariant::Type>(context->argument(1));
        QSqlField _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlField_throw_ambiguity_error_helper(context,
        qtscript_QSqlField_function_names[_id],
        qtscript_QSqlField_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlField_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlField*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlField*)0));
    for (int i = 0; i < 28; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlField_prototype_call, qtscript_QSqlField_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlField_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlField>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSqlField*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlField_static_call, proto, qtscript_QSqlField_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("RequiredStatus"),
        qtscript_create_QSqlField_RequiredStatus_class(engine, ctor));
    return ctor;
}
