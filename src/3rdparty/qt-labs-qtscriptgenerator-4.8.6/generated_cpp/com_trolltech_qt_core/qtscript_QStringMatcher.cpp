#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstringmatcher.h>
#include <QVariant>
#include <qstringmatcher.h>

static const char * const qtscript_QStringMatcher_function_names[] = {
    "QStringMatcher"
    // static
    // prototype
    , "caseSensitivity"
    , "indexIn"
    , "pattern"
    , "setCaseSensitivity"
    , "setPattern"
    , "toString"
};

static const char * const qtscript_QStringMatcher_function_signatures[] = {
    "\nString pattern, CaseSensitivity cs\nQStringMatcher other"
    // static
    // prototype
    , ""
    , "String str, int from"
    , ""
    , "CaseSensitivity cs"
    , "String pattern"
""
};

static const int qtscript_QStringMatcher_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 2
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QStringMatcher_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStringMatcher::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStringMatcher)
Q_DECLARE_METATYPE(QStringMatcher*)
Q_DECLARE_METATYPE(Qt::CaseSensitivity)

//
// QStringMatcher
//

static QScriptValue qtscript_QStringMatcher_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStringMatcher* _q_self = qscriptvalue_cast<QStringMatcher*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStringMatcher.%0(): this object is not a QStringMatcher")
            .arg(qtscript_QStringMatcher_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Qt::CaseSensitivity _q_result = _q_self->caseSensitivity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
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
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->pattern();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        Qt::CaseSensitivity _q_arg0 = qscriptvalue_cast<Qt::CaseSensitivity>(context->argument(0));
        _q_self->setCaseSensitivity(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPattern(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QStringMatcher");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStringMatcher_throw_ambiguity_error_helper(context,
        qtscript_QStringMatcher_function_names[_id+1],
        qtscript_QStringMatcher_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStringMatcher_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStringMatcher(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QStringMatcher _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QStringMatcher _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QStringMatcher>() == context->argument(0).toVariant().userType())) {
            QStringMatcher _q_arg0 = qscriptvalue_cast<QStringMatcher>(context->argument(0));
            QStringMatcher _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        Qt::CaseSensitivity _q_arg1 = qscriptvalue_cast<Qt::CaseSensitivity>(context->argument(1));
        QStringMatcher _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStringMatcher_throw_ambiguity_error_helper(context,
        qtscript_QStringMatcher_function_names[_id],
        qtscript_QStringMatcher_function_signatures[_id]);
}

QScriptValue qtscript_create_QStringMatcher_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStringMatcher*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStringMatcher*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStringMatcher_prototype_call, qtscript_QStringMatcher_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStringMatcher_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QStringMatcher>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStringMatcher*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStringMatcher_static_call, proto, qtscript_QStringMatcher_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
