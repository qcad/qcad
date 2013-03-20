#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextcodec.h>
#include <QVariant>
#include <qbytearray.h>
#include <qtextcodec.h>

static const char * const qtscript_QTextEncoder_function_names[] = {
    "QTextEncoder"
    // static
    // prototype
    , "fromUnicode"
    , "hasFailure"
    , "toString"
};

static const char * const qtscript_QTextEncoder_function_signatures[] = {
    "QTextCodec codec\nQTextCodec codec, ConversionFlags flags"
    // static
    // prototype
    , "String str"
    , ""
""
};

static const int qtscript_QTextEncoder_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTextEncoder_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextEncoder::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextEncoder*)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QFlags<QTextCodec::ConversionFlag>)

//
// QTextEncoder
//

static QScriptValue qtscript_QTextEncoder_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextEncoder* _q_self = qscriptvalue_cast<QTextEncoder*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextEncoder.%0(): this object is not a QTextEncoder")
            .arg(qtscript_QTextEncoder_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = _q_self->fromUnicode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasFailure();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QTextEncoder");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextEncoder_throw_ambiguity_error_helper(context,
        qtscript_QTextEncoder_function_names[_id+1],
        qtscript_QTextEncoder_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextEncoder_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextEncoder(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
        QTextEncoder* _q_cpp_result = new QTextEncoder(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
        QFlags<QTextCodec::ConversionFlag> _q_arg1 = qscriptvalue_cast<QFlags<QTextCodec::ConversionFlag> >(context->argument(1));
        QTextEncoder* _q_cpp_result = new QTextEncoder(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextEncoder_throw_ambiguity_error_helper(context,
        qtscript_QTextEncoder_function_names[_id],
        qtscript_QTextEncoder_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextEncoder_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextEncoder*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextEncoder*)0));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextEncoder_prototype_call, qtscript_QTextEncoder_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextEncoder_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextEncoder*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextEncoder_static_call, proto, qtscript_QTextEncoder_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
