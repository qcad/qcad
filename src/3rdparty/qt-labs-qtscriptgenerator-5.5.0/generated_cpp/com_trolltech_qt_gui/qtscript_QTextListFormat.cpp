#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextformat.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

#include "qtscriptshell_QTextListFormat.h"

static const char * const qtscript_QTextListFormat_function_names[] = {
    "QTextListFormat"
    // static
    // prototype
    , "indent"
    , "numberPrefix"
    , "numberSuffix"
    , "setIndent"
    , "setNumberPrefix"
    , "setNumberSuffix"
    , "setStyle"
    , "style"
    , "toString"
};

static const char * const qtscript_QTextListFormat_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , "int indent"
    , "String numberPrefix"
    , "String numberSuffix"
    , "Style style"
    , ""
""
};

static const int qtscript_QTextListFormat_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTextListFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextListFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextListFormat)
Q_DECLARE_METATYPE(QTextListFormat*)
Q_DECLARE_METATYPE(QtScriptShell_QTextListFormat)
Q_DECLARE_METATYPE(QtScriptShell_QTextListFormat*)
Q_DECLARE_METATYPE(QTextListFormat::Style)
Q_DECLARE_METATYPE(QTextFormat*)

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
// QTextListFormat::Style
//

static const QTextListFormat::Style qtscript_QTextListFormat_Style_values[] = {
    QTextListFormat::ListUpperRoman
    , QTextListFormat::ListLowerRoman
    , QTextListFormat::ListUpperAlpha
    , QTextListFormat::ListLowerAlpha
    , QTextListFormat::ListDecimal
    , QTextListFormat::ListSquare
    , QTextListFormat::ListCircle
    , QTextListFormat::ListDisc
    , QTextListFormat::ListStyleUndefined
};

static const char * const qtscript_QTextListFormat_Style_keys[] = {
    "ListUpperRoman"
    , "ListLowerRoman"
    , "ListUpperAlpha"
    , "ListLowerAlpha"
    , "ListDecimal"
    , "ListSquare"
    , "ListCircle"
    , "ListDisc"
    , "ListStyleUndefined"
};

static QString qtscript_QTextListFormat_Style_toStringHelper(QTextListFormat::Style value)
{
    if ((value >= QTextListFormat::ListUpperRoman) && (value <= QTextListFormat::ListStyleUndefined))
        return qtscript_QTextListFormat_Style_keys[static_cast<int>(value)-static_cast<int>(QTextListFormat::ListUpperRoman)];
    return QString();
}

static QScriptValue qtscript_QTextListFormat_Style_toScriptValue(QScriptEngine *engine, const QTextListFormat::Style &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextListFormat"));
    return clazz.property(qtscript_QTextListFormat_Style_toStringHelper(value));
}

static void qtscript_QTextListFormat_Style_fromScriptValue(const QScriptValue &value, QTextListFormat::Style &out)
{
    out = qvariant_cast<QTextListFormat::Style>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextListFormat_Style(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextListFormat::ListUpperRoman) && (arg <= QTextListFormat::ListStyleUndefined))
        return qScriptValueFromValue(engine,  static_cast<QTextListFormat::Style>(arg));
    return context->throwError(QString::fromLatin1("Style(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextListFormat_Style_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextListFormat::Style value = qscriptvalue_cast<QTextListFormat::Style>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextListFormat_Style_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextListFormat::Style value = qscriptvalue_cast<QTextListFormat::Style>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextListFormat_Style_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextListFormat_Style_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextListFormat_Style,
        qtscript_QTextListFormat_Style_valueOf, qtscript_QTextListFormat_Style_toString);
    qScriptRegisterMetaType<QTextListFormat::Style>(engine, qtscript_QTextListFormat_Style_toScriptValue,
        qtscript_QTextListFormat_Style_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 9; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextListFormat_Style_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextListFormat_Style_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextListFormat
//

static QScriptValue qtscript_QTextListFormat_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextListFormat* _q_self = qscriptvalue_cast<QTextListFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextListFormat.%0(): this object is not a QTextListFormat")
            .arg(qtscript_QTextListFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->indent();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->numberPrefix();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->numberSuffix();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setIndent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setNumberPrefix(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setNumberSuffix(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QTextListFormat::Style _q_arg0 = qscriptvalue_cast<QTextListFormat::Style>(context->argument(0));
        _q_self->setStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QTextListFormat::Style _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QTextListFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextListFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextListFormat_function_names[_id+1],
        qtscript_QTextListFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextListFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextListFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextListFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextListFormat)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextListFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextListFormat_function_names[_id],
        qtscript_QTextListFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextListFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextListFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextListFormat*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextFormat*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextListFormat_prototype_call, qtscript_QTextListFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextListFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextListFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextListFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextListFormat_static_call, proto, qtscript_QTextListFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Style"),
        qtscript_create_QTextListFormat_Style_class(engine, ctor));
    return ctor;
}
