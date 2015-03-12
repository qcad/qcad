#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qregexp.h>
#include <QStringList>
#include <QVariant>
#include <qregexp.h>
#include <qstringlist.h>

static const char * const qtscript_QRegExp_function_names[] = {
    "QRegExp"
    // static
    , "escape"
    // prototype
    , "cap"
    , "captureCount"
    , "capturedTexts"
    , "caseSensitivity"
    , "errorString"
    , "exactMatch"
    , "indexIn"
    , "isEmpty"
    , "isMinimal"
    , "isValid"
    , "lastIndexIn"
    , "matchedLength"
    , "equals"
    , "pattern"
    , "patternSyntax"
    , "pos"
    , "setCaseSensitivity"
    , "setMinimal"
    , "setPattern"
    , "setPatternSyntax"
    , "swap"
    , "toString"
};

static const char * const qtscript_QRegExp_function_signatures[] = {
    "\nQRegExp rx\nString pattern, CaseSensitivity cs, PatternSyntax syntax"
    // static
    , "String str"
    // prototype
    , "int nth"
    , ""
    , ""
    , ""
    , ""
    , "String str"
    , "String str, int offset, CaretMode caretMode"
    , ""
    , ""
    , ""
    , "String str, int offset, CaretMode caretMode"
    , ""
    , "QRegExp rx"
    , ""
    , ""
    , "int nth"
    , "CaseSensitivity cs"
    , "bool minimal"
    , "String pattern"
    , "PatternSyntax syntax"
    , "QRegExp other"
""
};

static const int qtscript_QRegExp_function_lengths[] = {
    3
    // static
    , 1
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 3
    , 0
    , 0
    , 0
    , 3
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
    , 0
};

static QScriptValue qtscript_QRegExp_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRegExp::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRegExp*)
Q_DECLARE_METATYPE(QRegExp::CaretMode)
Q_DECLARE_METATYPE(QRegExp::PatternSyntax)
Q_DECLARE_METATYPE(Qt::CaseSensitivity)

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
// QRegExp::CaretMode
//

static const QRegExp::CaretMode qtscript_QRegExp_CaretMode_values[] = {
    QRegExp::CaretAtZero
    , QRegExp::CaretAtOffset
    , QRegExp::CaretWontMatch
};

static const char * const qtscript_QRegExp_CaretMode_keys[] = {
    "CaretAtZero"
    , "CaretAtOffset"
    , "CaretWontMatch"
};

static QString qtscript_QRegExp_CaretMode_toStringHelper(QRegExp::CaretMode value)
{
    if ((value >= QRegExp::CaretAtZero) && (value <= QRegExp::CaretWontMatch))
        return qtscript_QRegExp_CaretMode_keys[static_cast<int>(value)-static_cast<int>(QRegExp::CaretAtZero)];
    return QString();
}

static QScriptValue qtscript_QRegExp_CaretMode_toScriptValue(QScriptEngine *engine, const QRegExp::CaretMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QRegExp"));
    return clazz.property(qtscript_QRegExp_CaretMode_toStringHelper(value));
}

static void qtscript_QRegExp_CaretMode_fromScriptValue(const QScriptValue &value, QRegExp::CaretMode &out)
{
    out = qvariant_cast<QRegExp::CaretMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QRegExp_CaretMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QRegExp::CaretAtZero) && (arg <= QRegExp::CaretWontMatch))
        return qScriptValueFromValue(engine,  static_cast<QRegExp::CaretMode>(arg));
    return context->throwError(QString::fromLatin1("CaretMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QRegExp_CaretMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QRegExp::CaretMode value = qscriptvalue_cast<QRegExp::CaretMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QRegExp_CaretMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QRegExp::CaretMode value = qscriptvalue_cast<QRegExp::CaretMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QRegExp_CaretMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QRegExp_CaretMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QRegExp_CaretMode,
        qtscript_QRegExp_CaretMode_valueOf, qtscript_QRegExp_CaretMode_toString);
    qScriptRegisterMetaType<QRegExp::CaretMode>(engine, qtscript_QRegExp_CaretMode_toScriptValue,
        qtscript_QRegExp_CaretMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QRegExp_CaretMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QRegExp_CaretMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QRegExp::PatternSyntax
//

static const QRegExp::PatternSyntax qtscript_QRegExp_PatternSyntax_values[] = {
    QRegExp::RegExp
    , QRegExp::Wildcard
    , QRegExp::FixedString
    , QRegExp::RegExp2
    , QRegExp::WildcardUnix
    , QRegExp::W3CXmlSchema11
};

static const char * const qtscript_QRegExp_PatternSyntax_keys[] = {
    "RegExp"
    , "Wildcard"
    , "FixedString"
    , "RegExp2"
    , "WildcardUnix"
    , "W3CXmlSchema11"
};

static QString qtscript_QRegExp_PatternSyntax_toStringHelper(QRegExp::PatternSyntax value)
{
    if ((value >= QRegExp::RegExp) && (value <= QRegExp::W3CXmlSchema11))
        return qtscript_QRegExp_PatternSyntax_keys[static_cast<int>(value)-static_cast<int>(QRegExp::RegExp)];
    return QString();
}

static QScriptValue qtscript_QRegExp_PatternSyntax_toScriptValue(QScriptEngine *engine, const QRegExp::PatternSyntax &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QRegExp"));
    return clazz.property(qtscript_QRegExp_PatternSyntax_toStringHelper(value));
}

static void qtscript_QRegExp_PatternSyntax_fromScriptValue(const QScriptValue &value, QRegExp::PatternSyntax &out)
{
    out = qvariant_cast<QRegExp::PatternSyntax>(value.toVariant());
}

static QScriptValue qtscript_construct_QRegExp_PatternSyntax(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QRegExp::RegExp) && (arg <= QRegExp::W3CXmlSchema11))
        return qScriptValueFromValue(engine,  static_cast<QRegExp::PatternSyntax>(arg));
    return context->throwError(QString::fromLatin1("PatternSyntax(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QRegExp_PatternSyntax_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QRegExp::PatternSyntax value = qscriptvalue_cast<QRegExp::PatternSyntax>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QRegExp_PatternSyntax_toString(QScriptContext *context, QScriptEngine *engine)
{
    QRegExp::PatternSyntax value = qscriptvalue_cast<QRegExp::PatternSyntax>(context->thisObject());
    return QScriptValue(engine, qtscript_QRegExp_PatternSyntax_toStringHelper(value));
}

static QScriptValue qtscript_create_QRegExp_PatternSyntax_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QRegExp_PatternSyntax,
        qtscript_QRegExp_PatternSyntax_valueOf, qtscript_QRegExp_PatternSyntax_toString);
    qScriptRegisterMetaType<QRegExp::PatternSyntax>(engine, qtscript_QRegExp_PatternSyntax_toScriptValue,
        qtscript_QRegExp_PatternSyntax_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QRegExp_PatternSyntax_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QRegExp_PatternSyntax_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QRegExp
//

static QScriptValue qtscript_QRegExp_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 21;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QRegExp* _q_self = qscriptvalue_cast<QRegExp*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRegExp.%0(): this object is not a QRegExp")
            .arg(qtscript_QRegExp_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->cap();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->cap(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->captureCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->capturedTexts();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        Qt::CaseSensitivity _q_result = _q_self->caseSensitivity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->exactMatch(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->indexIn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->indexIn(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QRegExp::CaretMode _q_arg2 = qscriptvalue_cast<QRegExp::CaretMode>(context->argument(2));
        int _q_result = _q_self->indexIn(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isMinimal();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->lastIndexIn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->lastIndexIn(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QRegExp::CaretMode _q_arg2 = qscriptvalue_cast<QRegExp::CaretMode>(context->argument(2));
        int _q_result = _q_self->lastIndexIn(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->matchedLength();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QRegExp _q_arg0 = context->argument(0).toRegExp();
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->pattern();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QRegExp::PatternSyntax _q_result = _q_self->patternSyntax();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->pos();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->pos(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        Qt::CaseSensitivity _q_arg0 = qscriptvalue_cast<Qt::CaseSensitivity>(context->argument(0));
        _q_self->setCaseSensitivity(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setMinimal(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPattern(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QRegExp::PatternSyntax _q_arg0 = qscriptvalue_cast<QRegExp::PatternSyntax>(context->argument(0));
        _q_self->setPatternSyntax(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QRegExp _q_arg0 = context->argument(0).toRegExp();
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRegExp_throw_ambiguity_error_helper(context,
        qtscript_QRegExp_function_names[_id+2],
        qtscript_QRegExp_function_signatures[_id+2]);
}

static QScriptValue qtscript_QRegExp_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRegExp(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QRegExp _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isRegExp()) {
            QRegExp _q_arg0 = context->argument(0).toRegExp();
            QRegExp _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QRegExp _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        Qt::CaseSensitivity _q_arg1 = qscriptvalue_cast<Qt::CaseSensitivity>(context->argument(1));
        QRegExp _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        Qt::CaseSensitivity _q_arg1 = qscriptvalue_cast<Qt::CaseSensitivity>(context->argument(1));
        QRegExp::PatternSyntax _q_arg2 = qscriptvalue_cast<QRegExp::PatternSyntax>(context->argument(2));
        QRegExp _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QRegExp::escape(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRegExp_throw_ambiguity_error_helper(context,
        qtscript_QRegExp_function_names[_id],
        qtscript_QRegExp_function_signatures[_id]);
}

QScriptValue qtscript_create_QRegExp_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRegExp*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRegExp*)0));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRegExp_prototype_call, qtscript_QRegExp_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QRegExp_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QRegExp>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QRegExp*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRegExp_static_call, proto, qtscript_QRegExp_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRegExp_static_call,
            qtscript_QRegExp_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QRegExp_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("CaretMode"),
        qtscript_create_QRegExp_CaretMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PatternSyntax"),
        qtscript_create_QRegExp_PatternSyntax_class(engine, ctor));
    return ctor;
}
