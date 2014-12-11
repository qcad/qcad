#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextboundaryfinder.h>
#include <QVariant>
#include <qtextboundaryfinder.h>

static const char * const qtscript_QTextBoundaryFinder_function_names[] = {
    "QTextBoundaryFinder"
    // static
    // prototype
    , "boundaryReasons"
    , "isAtBoundary"
    , "isValid"
    , "position"
    , "setPosition"
    , "string"
    , "toEnd"
    , "toNextBoundary"
    , "toPreviousBoundary"
    , "toStart"
    , "type"
    , "toString"
};

static const char * const qtscript_QTextBoundaryFinder_function_signatures[] = {
    "\nBoundaryType type, String string\nQTextBoundaryFinder other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "int position"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTextBoundaryFinder_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextBoundaryFinder_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextBoundaryFinder::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextBoundaryFinder)
Q_DECLARE_METATYPE(QTextBoundaryFinder*)
Q_DECLARE_METATYPE(QTextBoundaryFinder::BoundaryReason)
Q_DECLARE_METATYPE(QFlags<QTextBoundaryFinder::BoundaryReason>)
Q_DECLARE_METATYPE(QTextBoundaryFinder::BoundaryType)

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
// QTextBoundaryFinder::BoundaryReason
//

static const QTextBoundaryFinder::BoundaryReason qtscript_QTextBoundaryFinder_BoundaryReason_values[] = {
    QTextBoundaryFinder::NotAtBoundary
    , QTextBoundaryFinder::BreakOpportunity
    , QTextBoundaryFinder::StartOfItem
    , QTextBoundaryFinder::EndOfItem
    , QTextBoundaryFinder::MandatoryBreak
    , QTextBoundaryFinder::SoftHyphen
};

static const char * const qtscript_QTextBoundaryFinder_BoundaryReason_keys[] = {
    "NotAtBoundary"
    , "BreakOpportunity"
    , "StartOfItem"
    , "EndOfItem"
    , "MandatoryBreak"
    , "SoftHyphen"
};

static QString qtscript_QTextBoundaryFinder_BoundaryReason_toStringHelper(QTextBoundaryFinder::BoundaryReason value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QTextBoundaryFinder_BoundaryReason_values[i] == value)
            return QString::fromLatin1(qtscript_QTextBoundaryFinder_BoundaryReason_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryReason_toScriptValue(QScriptEngine *engine, const QTextBoundaryFinder::BoundaryReason &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextBoundaryFinder"));
    return clazz.property(qtscript_QTextBoundaryFinder_BoundaryReason_toStringHelper(value));
}

static void qtscript_QTextBoundaryFinder_BoundaryReason_fromScriptValue(const QScriptValue &value, QTextBoundaryFinder::BoundaryReason &out)
{
    out = qvariant_cast<QTextBoundaryFinder::BoundaryReason>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextBoundaryFinder_BoundaryReason(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QTextBoundaryFinder_BoundaryReason_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTextBoundaryFinder::BoundaryReason>(arg));
    }
    return context->throwError(QString::fromLatin1("BoundaryReason(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryReason_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextBoundaryFinder::BoundaryReason value = qscriptvalue_cast<QTextBoundaryFinder::BoundaryReason>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryReason_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextBoundaryFinder::BoundaryReason value = qscriptvalue_cast<QTextBoundaryFinder::BoundaryReason>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextBoundaryFinder_BoundaryReason_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextBoundaryFinder_BoundaryReason_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextBoundaryFinder_BoundaryReason,
        qtscript_QTextBoundaryFinder_BoundaryReason_valueOf, qtscript_QTextBoundaryFinder_BoundaryReason_toString);
    qScriptRegisterMetaType<QTextBoundaryFinder::BoundaryReason>(engine, qtscript_QTextBoundaryFinder_BoundaryReason_toScriptValue,
        qtscript_QTextBoundaryFinder_BoundaryReason_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextBoundaryFinder_BoundaryReason_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextBoundaryFinder_BoundaryReason_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextBoundaryFinder::BoundaryReasons
//

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryReasons_toScriptValue(QScriptEngine *engine, const QTextBoundaryFinder::BoundaryReasons &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QTextBoundaryFinder_BoundaryReasons_fromScriptValue(const QScriptValue &value, QTextBoundaryFinder::BoundaryReasons &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QTextBoundaryFinder::BoundaryReasons>())
        out = qvariant_cast<QTextBoundaryFinder::BoundaryReasons>(var);
    else if (var.userType() == qMetaTypeId<QTextBoundaryFinder::BoundaryReason>())
        out = qvariant_cast<QTextBoundaryFinder::BoundaryReason>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QTextBoundaryFinder_BoundaryReasons(QScriptContext *context, QScriptEngine *engine)
{
    QTextBoundaryFinder::BoundaryReasons result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QTextBoundaryFinder::BoundaryReasons>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QTextBoundaryFinder::BoundaryReason>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("BoundaryReasons(): argument %0 is not of type BoundaryReason").arg(i));
            }
            result |= qvariant_cast<QTextBoundaryFinder::BoundaryReason>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryReasons_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextBoundaryFinder::BoundaryReasons value = qscriptvalue_cast<QTextBoundaryFinder::BoundaryReasons>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryReasons_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextBoundaryFinder::BoundaryReasons value = qscriptvalue_cast<QTextBoundaryFinder::BoundaryReasons>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_QTextBoundaryFinder_BoundaryReason_values[i]) == qtscript_QTextBoundaryFinder_BoundaryReason_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QTextBoundaryFinder_BoundaryReason_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryReasons_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QTextBoundaryFinder::BoundaryReasons>() == otherObj.value<QTextBoundaryFinder::BoundaryReasons>())));
}

static QScriptValue qtscript_create_QTextBoundaryFinder_BoundaryReasons_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QTextBoundaryFinder_BoundaryReasons, qtscript_QTextBoundaryFinder_BoundaryReasons_valueOf,
        qtscript_QTextBoundaryFinder_BoundaryReasons_toString, qtscript_QTextBoundaryFinder_BoundaryReasons_equals);
    qScriptRegisterMetaType<QTextBoundaryFinder::BoundaryReasons>(engine, qtscript_QTextBoundaryFinder_BoundaryReasons_toScriptValue,
        qtscript_QTextBoundaryFinder_BoundaryReasons_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QTextBoundaryFinder::BoundaryType
//

static const QTextBoundaryFinder::BoundaryType qtscript_QTextBoundaryFinder_BoundaryType_values[] = {
    QTextBoundaryFinder::Grapheme
    , QTextBoundaryFinder::Word
    , QTextBoundaryFinder::Sentence
    , QTextBoundaryFinder::Line
};

static const char * const qtscript_QTextBoundaryFinder_BoundaryType_keys[] = {
    "Grapheme"
    , "Word"
    , "Sentence"
    , "Line"
};

static QString qtscript_QTextBoundaryFinder_BoundaryType_toStringHelper(QTextBoundaryFinder::BoundaryType value)
{
    if ((value >= QTextBoundaryFinder::Grapheme) && (value <= QTextBoundaryFinder::Line))
        return qtscript_QTextBoundaryFinder_BoundaryType_keys[static_cast<int>(value)-static_cast<int>(QTextBoundaryFinder::Grapheme)];
    return QString();
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryType_toScriptValue(QScriptEngine *engine, const QTextBoundaryFinder::BoundaryType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextBoundaryFinder"));
    return clazz.property(qtscript_QTextBoundaryFinder_BoundaryType_toStringHelper(value));
}

static void qtscript_QTextBoundaryFinder_BoundaryType_fromScriptValue(const QScriptValue &value, QTextBoundaryFinder::BoundaryType &out)
{
    out = qvariant_cast<QTextBoundaryFinder::BoundaryType>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextBoundaryFinder_BoundaryType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextBoundaryFinder::Grapheme) && (arg <= QTextBoundaryFinder::Line))
        return qScriptValueFromValue(engine,  static_cast<QTextBoundaryFinder::BoundaryType>(arg));
    return context->throwError(QString::fromLatin1("BoundaryType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextBoundaryFinder::BoundaryType value = qscriptvalue_cast<QTextBoundaryFinder::BoundaryType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextBoundaryFinder_BoundaryType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextBoundaryFinder::BoundaryType value = qscriptvalue_cast<QTextBoundaryFinder::BoundaryType>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextBoundaryFinder_BoundaryType_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextBoundaryFinder_BoundaryType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextBoundaryFinder_BoundaryType,
        qtscript_QTextBoundaryFinder_BoundaryType_valueOf, qtscript_QTextBoundaryFinder_BoundaryType_toString);
    qScriptRegisterMetaType<QTextBoundaryFinder::BoundaryType>(engine, qtscript_QTextBoundaryFinder_BoundaryType_toScriptValue,
        qtscript_QTextBoundaryFinder_BoundaryType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextBoundaryFinder_BoundaryType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextBoundaryFinder_BoundaryType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextBoundaryFinder
//

static QScriptValue qtscript_QTextBoundaryFinder_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextBoundaryFinder* _q_self = qscriptvalue_cast<QTextBoundaryFinder*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextBoundaryFinder.%0(): this object is not a QTextBoundaryFinder")
            .arg(qtscript_QTextBoundaryFinder_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<QTextBoundaryFinder::BoundaryReason> _q_result = _q_self->boundaryReasons();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAtBoundary();
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
        int _q_result = _q_self->position();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPosition(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->string();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->toEnd();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->toNextBoundary();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->toPreviousBoundary();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->toStart();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QTextBoundaryFinder::BoundaryType _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11: {
    QString result = QString::fromLatin1("QTextBoundaryFinder");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBoundaryFinder_throw_ambiguity_error_helper(context,
        qtscript_QTextBoundaryFinder_function_names[_id+1],
        qtscript_QTextBoundaryFinder_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextBoundaryFinder_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextBoundaryFinder(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextBoundaryFinder _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QTextBoundaryFinder _q_arg0 = qscriptvalue_cast<QTextBoundaryFinder>(context->argument(0));
        QTextBoundaryFinder _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QTextBoundaryFinder::BoundaryType _q_arg0 = qscriptvalue_cast<QTextBoundaryFinder::BoundaryType>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QTextBoundaryFinder _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBoundaryFinder_throw_ambiguity_error_helper(context,
        qtscript_QTextBoundaryFinder_function_names[_id],
        qtscript_QTextBoundaryFinder_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextBoundaryFinder_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextBoundaryFinder*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextBoundaryFinder*)0));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextBoundaryFinder_prototype_call, qtscript_QTextBoundaryFinder_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextBoundaryFinder_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextBoundaryFinder>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextBoundaryFinder*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextBoundaryFinder_static_call, proto, qtscript_QTextBoundaryFinder_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("BoundaryReason"),
        qtscript_create_QTextBoundaryFinder_BoundaryReason_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BoundaryReasons"),
        qtscript_create_QTextBoundaryFinder_BoundaryReasons_class(engine));
    ctor.setProperty(QString::fromLatin1("BoundaryType"),
        qtscript_create_QTextBoundaryFinder_BoundaryType_class(engine, ctor));
    return ctor;
}
