#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbytearraymatcher.h>
#include <QVariant>
#include <qbytearray.h>
#include <qbytearraymatcher.h>

static const char * const qtscript_QByteArrayMatcher_function_names[] = {
    "QByteArrayMatcher"
    // static
    // prototype
    , "indexIn"
    , "pattern"
    , "setPattern"
    , "toString"
};

static const char * const qtscript_QByteArrayMatcher_function_signatures[] = {
    "\nQByteArray pattern\nQByteArrayMatcher other\nchar pattern, int length"
    // static
    // prototype
    , "QByteArray ba, int from\nchar str, int len, int from"
    , ""
    , "QByteArray pattern"
""
};

static const int qtscript_QByteArrayMatcher_function_lengths[] = {
    2
    // static
    // prototype
    , 3
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QByteArrayMatcher_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QByteArrayMatcher::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QByteArrayMatcher)
Q_DECLARE_METATYPE(QByteArrayMatcher*)
Q_DECLARE_METATYPE(char*)

//
// QByteArrayMatcher
//

static QScriptValue qtscript_QByteArrayMatcher_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QByteArrayMatcher* _q_self = qscriptvalue_cast<QByteArrayMatcher*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QByteArrayMatcher.%0(): this object is not a QByteArrayMatcher")
            .arg(qtscript_QByteArrayMatcher_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        int _q_result = _q_self->indexIn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_result = _q_self->indexIn(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<char*>(context->argument(0))
            && context->argument(1).isNumber()) {
            char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_result = _q_self->indexIn(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_result = _q_self->indexIn(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->pattern();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setPattern(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QByteArrayMatcher");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QByteArrayMatcher_throw_ambiguity_error_helper(context,
        qtscript_QByteArrayMatcher_function_names[_id+1],
        qtscript_QByteArrayMatcher_function_signatures[_id+1]);
}

static QScriptValue qtscript_QByteArrayMatcher_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QByteArrayMatcher(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QByteArrayMatcher _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QByteArrayMatcher _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArrayMatcher>() == context->argument(0).toVariant().userType())) {
            QByteArrayMatcher _q_arg0 = qscriptvalue_cast<QByteArrayMatcher>(context->argument(0));
            QByteArrayMatcher _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QByteArrayMatcher _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QByteArrayMatcher_throw_ambiguity_error_helper(context,
        qtscript_QByteArrayMatcher_function_names[_id],
        qtscript_QByteArrayMatcher_function_signatures[_id]);
}

QScriptValue qtscript_create_QByteArrayMatcher_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QByteArrayMatcher*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QByteArrayMatcher*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QByteArrayMatcher_prototype_call, qtscript_QByteArrayMatcher_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QByteArrayMatcher_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QByteArrayMatcher>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QByteArrayMatcher*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QByteArrayMatcher_static_call, proto, qtscript_QByteArrayMatcher_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
