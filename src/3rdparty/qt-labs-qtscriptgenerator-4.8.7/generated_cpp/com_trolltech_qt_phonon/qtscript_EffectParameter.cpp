#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <effectparameter.h>
#include <QVariant>
#include <qlist.h>

static const char * const qtscript_EffectParameter_function_names[] = {
    "EffectParameter"
    // static
    // prototype
    , "defaultValue"
    , "description"
    , "isLogarithmicControl"
    , "maximumValue"
    , "minimumValue"
    , "name"
    , "possibleValues"
    , "type"
    , "toString"
};

static const char * const qtscript_EffectParameter_function_signatures[] = {
    "int parameterId, String name, Hints hints, Object defaultValue, Object min, Object max, List values, String description"
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
""
};

static const int qtscript_EffectParameter_function_lengths[] = {
    8
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
};

static QScriptValue qtscript_EffectParameter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("EffectParameter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::EffectParameter*)
Q_DECLARE_METATYPE(Phonon::EffectParameter::Hint)
Q_DECLARE_METATYPE(QFlags<Phonon::EffectParameter::Hint>)
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
// Phonon::EffectParameter::Hint
//

static const Phonon::EffectParameter::Hint qtscript_EffectParameter_Hint_values[] = {
    Phonon::EffectParameter::ToggledHint
    , Phonon::EffectParameter::LogarithmicHint
    , Phonon::EffectParameter::IntegerHint
};

static const char * const qtscript_EffectParameter_Hint_keys[] = {
    "ToggledHint"
    , "LogarithmicHint"
    , "IntegerHint"
};

static QString qtscript_EffectParameter_Hint_toStringHelper(Phonon::EffectParameter::Hint value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_EffectParameter_Hint_values[i] == value)
            return QString::fromLatin1(qtscript_EffectParameter_Hint_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_EffectParameter_Hint_toScriptValue(QScriptEngine *engine, const Phonon::EffectParameter::Hint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("EffectParameter"));
    return clazz.property(qtscript_EffectParameter_Hint_toStringHelper(value));
}

static void qtscript_EffectParameter_Hint_fromScriptValue(const QScriptValue &value, Phonon::EffectParameter::Hint &out)
{
    out = qvariant_cast<Phonon::EffectParameter::Hint>(value.toVariant());
}

static QScriptValue qtscript_construct_EffectParameter_Hint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_EffectParameter_Hint_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Phonon::EffectParameter::Hint>(arg));
    }
    return context->throwError(QString::fromLatin1("Hint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_EffectParameter_Hint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::EffectParameter::Hint value = qscriptvalue_cast<Phonon::EffectParameter::Hint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_EffectParameter_Hint_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::EffectParameter::Hint value = qscriptvalue_cast<Phonon::EffectParameter::Hint>(context->thisObject());
    return QScriptValue(engine, qtscript_EffectParameter_Hint_toStringHelper(value));
}

static QScriptValue qtscript_create_EffectParameter_Hint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_EffectParameter_Hint,
        qtscript_EffectParameter_Hint_valueOf, qtscript_EffectParameter_Hint_toString);
    qScriptRegisterMetaType<Phonon::EffectParameter::Hint>(engine, qtscript_EffectParameter_Hint_toScriptValue,
        qtscript_EffectParameter_Hint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_EffectParameter_Hint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_EffectParameter_Hint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::EffectParameter::Hints
//

static QScriptValue qtscript_EffectParameter_Hints_toScriptValue(QScriptEngine *engine, const Phonon::EffectParameter::Hints &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_EffectParameter_Hints_fromScriptValue(const QScriptValue &value, Phonon::EffectParameter::Hints &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Phonon::EffectParameter::Hints>())
        out = qvariant_cast<Phonon::EffectParameter::Hints>(var);
    else if (var.userType() == qMetaTypeId<Phonon::EffectParameter::Hint>())
        out = qvariant_cast<Phonon::EffectParameter::Hint>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_EffectParameter_Hints(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::EffectParameter::Hints result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Phonon::EffectParameter::Hints>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Phonon::EffectParameter::Hint>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Hints(): argument %0 is not of type Hint").arg(i));
            }
            result |= qvariant_cast<Phonon::EffectParameter::Hint>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_EffectParameter_Hints_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::EffectParameter::Hints value = qscriptvalue_cast<Phonon::EffectParameter::Hints>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_EffectParameter_Hints_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::EffectParameter::Hints value = qscriptvalue_cast<Phonon::EffectParameter::Hints>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_EffectParameter_Hint_values[i]) == qtscript_EffectParameter_Hint_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_EffectParameter_Hint_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_EffectParameter_Hints_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Phonon::EffectParameter::Hints>() == otherObj.value<Phonon::EffectParameter::Hints>())));
}

static QScriptValue qtscript_create_EffectParameter_Hints_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_EffectParameter_Hints, qtscript_EffectParameter_Hints_valueOf,
        qtscript_EffectParameter_Hints_toString, qtscript_EffectParameter_Hints_equals);
    qScriptRegisterMetaType<Phonon::EffectParameter::Hints>(engine, qtscript_EffectParameter_Hints_toScriptValue,
        qtscript_EffectParameter_Hints_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// EffectParameter
//

static QScriptValue qtscript_EffectParameter_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::EffectParameter* _q_self = qscriptvalue_cast<Phonon::EffectParameter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("EffectParameter.%0(): this object is not a EffectParameter")
            .arg(qtscript_EffectParameter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->defaultValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->description();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLogarithmicControl();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->maximumValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->minimumValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QList<QVariant> _q_result = _q_self->possibleValues();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QVariant::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("EffectParameter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_EffectParameter_throw_ambiguity_error_helper(context,
        qtscript_EffectParameter_function_names[_id+1],
        qtscript_EffectParameter_function_signatures[_id+1]);
}

static QScriptValue qtscript_EffectParameter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("EffectParameter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 7) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        QFlags<Phonon::EffectParameter::Hint> _q_arg2 = qscriptvalue_cast<QFlags<Phonon::EffectParameter::Hint> >(context->argument(2));
        QVariant _q_arg3 = context->argument(3).toVariant();
        QVariant _q_arg4 = context->argument(4).toVariant();
        QVariant _q_arg5 = context->argument(5).toVariant();
        QList<QVariant> _q_arg6;
        qScriptValueToSequence(context->argument(6), _q_arg6);
        Phonon::EffectParameter* _q_cpp_result = new Phonon::EffectParameter(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 8) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        QFlags<Phonon::EffectParameter::Hint> _q_arg2 = qscriptvalue_cast<QFlags<Phonon::EffectParameter::Hint> >(context->argument(2));
        QVariant _q_arg3 = context->argument(3).toVariant();
        QVariant _q_arg4 = context->argument(4).toVariant();
        QVariant _q_arg5 = context->argument(5).toVariant();
        QList<QVariant> _q_arg6;
        qScriptValueToSequence(context->argument(6), _q_arg6);
        QString _q_arg7 = context->argument(7).toString();
        Phonon::EffectParameter* _q_cpp_result = new Phonon::EffectParameter(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_EffectParameter_throw_ambiguity_error_helper(context,
        qtscript_EffectParameter_function_names[_id],
        qtscript_EffectParameter_function_signatures[_id]);
}

QScriptValue qtscript_create_EffectParameter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::EffectParameter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::EffectParameter*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_EffectParameter_prototype_call, qtscript_EffectParameter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_EffectParameter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::EffectParameter*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_EffectParameter_static_call, proto, qtscript_EffectParameter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Hint"),
        qtscript_create_EffectParameter_Hint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Hints"),
        qtscript_create_EffectParameter_Hints_class(engine));
    return ctor;
}
