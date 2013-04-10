#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextobject.h>
#include <QVariant>
#include <qtextformat.h>
#include <qtextobject.h>

static const char * const qtscript_QTextFragment_function_names[] = {
    "QTextFragment"
    // static
    // prototype
    , "charFormat"
    , "charFormatIndex"
    , "contains"
    , "isValid"
    , "length"
    , "equals"
    , "operator_less"
    , "position"
    , "text"
    , "toString"
};

static const char * const qtscript_QTextFragment_function_signatures[] = {
    "\nQTextFragment o"
    // static
    // prototype
    , ""
    , ""
    , "int position"
    , ""
    , ""
    , "QTextFragment o"
    , "QTextFragment o"
    , ""
    , ""
""
};

static const int qtscript_QTextFragment_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextFragment_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextFragment::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextFragment)
Q_DECLARE_METATYPE(QTextFragment*)
Q_DECLARE_METATYPE(QTextCharFormat)

//
// QTextFragment
//

static QScriptValue qtscript_QTextFragment_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextFragment* _q_self = qscriptvalue_cast<QTextFragment*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextFragment.%0(): this object is not a QTextFragment")
            .arg(qtscript_QTextFragment_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->charFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->charFormatIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QTextFragment _q_arg0 = qscriptvalue_cast<QTextFragment>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QTextFragment _q_arg0 = qscriptvalue_cast<QTextFragment>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->position();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QTextFragment");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFragment_throw_ambiguity_error_helper(context,
        qtscript_QTextFragment_function_names[_id+1],
        qtscript_QTextFragment_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextFragment_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextFragment(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextFragment _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QTextFragment _q_arg0 = qscriptvalue_cast<QTextFragment>(context->argument(0));
        QTextFragment _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFragment_throw_ambiguity_error_helper(context,
        qtscript_QTextFragment_function_names[_id],
        qtscript_QTextFragment_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextFragment_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextFragment*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextFragment*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextFragment_prototype_call, qtscript_QTextFragment_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextFragment_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextFragment>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextFragment*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextFragment_static_call, proto, qtscript_QTextFragment_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
