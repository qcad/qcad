#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsourcelocation.h>
#include <QVariant>
#include <qsourcelocation.h>
#include <qurl.h>

static const char * const qtscript_QSourceLocation_function_names[] = {
    "QSourceLocation"
    // static
    // prototype
    , "column"
    , "isNull"
    , "line"
    , "equals"
    , "setColumn"
    , "setLine"
    , "setUri"
    , "uri"
    , "toString"
};

static const char * const qtscript_QSourceLocation_function_signatures[] = {
    "\nQSourceLocation other\nQUrl uri, int line, int column"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "QSourceLocation other"
    , "qint64 newColumn"
    , "qint64 newLine"
    , "QUrl newUri"
    , ""
""
};

static const int qtscript_QSourceLocation_function_lengths[] = {
    3
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

static QScriptValue qtscript_QSourceLocation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSourceLocation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSourceLocation*)

//
// QSourceLocation
//

static QScriptValue qtscript_QSourceLocation_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSourceLocation* _q_self = qscriptvalue_cast<QSourceLocation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSourceLocation.%0(): this object is not a QSourceLocation")
            .arg(qtscript_QSourceLocation_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->column();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->line();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QSourceLocation _q_arg0 = qscriptvalue_cast<QSourceLocation>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setColumn(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setLine(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->setUri(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->uri();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSourceLocation_throw_ambiguity_error_helper(context,
        qtscript_QSourceLocation_function_names[_id+1],
        qtscript_QSourceLocation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSourceLocation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSourceLocation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSourceLocation _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSourceLocation>() == context->argument(0).toVariant().userType())) {
            QSourceLocation _q_arg0 = qscriptvalue_cast<QSourceLocation>(context->argument(0));
            QSourceLocation _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            QSourceLocation _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QSourceLocation _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QSourceLocation _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSourceLocation_throw_ambiguity_error_helper(context,
        qtscript_QSourceLocation_function_names[_id],
        qtscript_QSourceLocation_function_signatures[_id]);
}

QScriptValue qtscript_create_QSourceLocation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSourceLocation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSourceLocation*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSourceLocation_prototype_call, qtscript_QSourceLocation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSourceLocation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSourceLocation>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSourceLocation*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSourceLocation_static_call, proto, qtscript_QSourceLocation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
