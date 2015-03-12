#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qprocess.h>
#include <QVariant>
#include <qprocess.h>
#include <qstringlist.h>

static const char * const qtscript_QProcessEnvironment_function_names[] = {
    "QProcessEnvironment"
    // static
    , "systemEnvironment"
    // prototype
    , "clear"
    , "contains"
    , "insert"
    , "isEmpty"
    , "keys"
    , "operator_assign"
    , "equals"
    , "remove"
    , "swap"
    , "toStringList"
    , "value"
    , "toString"
};

static const char * const qtscript_QProcessEnvironment_function_signatures[] = {
    "\nQProcessEnvironment other"
    // static
    , ""
    // prototype
    , ""
    , "String name"
    , "QProcessEnvironment e\nString name, String value"
    , ""
    , ""
    , "QProcessEnvironment other"
    , "QProcessEnvironment other"
    , "String name"
    , "QProcessEnvironment other"
    , ""
    , "String name, String defaultValue"
""
};

static const int qtscript_QProcessEnvironment_function_lengths[] = {
    1
    // static
    , 0
    // prototype
    , 0
    , 1
    , 2
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_QProcessEnvironment_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QProcessEnvironment::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QProcessEnvironment)
Q_DECLARE_METATYPE(QProcessEnvironment*)

//
// QProcessEnvironment
//

static QScriptValue qtscript_QProcessEnvironment_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QProcessEnvironment* _q_self = qscriptvalue_cast<QProcessEnvironment*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QProcessEnvironment.%0(): this object is not a QProcessEnvironment")
            .arg(qtscript_QProcessEnvironment_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QProcessEnvironment _q_arg0 = qscriptvalue_cast<QProcessEnvironment>(context->argument(0));
        _q_self->insert(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->insert(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->keys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QProcessEnvironment _q_arg0 = qscriptvalue_cast<QProcessEnvironment>(context->argument(0));
        QProcessEnvironment& _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QProcessEnvironment _q_arg0 = qscriptvalue_cast<QProcessEnvironment>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->remove(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QProcessEnvironment _q_arg0 = qscriptvalue_cast<QProcessEnvironment>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->toStringList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->value(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = _q_self->value(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11: {
    QString result = QString::fromLatin1("QProcessEnvironment");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QProcessEnvironment_throw_ambiguity_error_helper(context,
        qtscript_QProcessEnvironment_function_names[_id+2],
        qtscript_QProcessEnvironment_function_signatures[_id+2]);
}

static QScriptValue qtscript_QProcessEnvironment_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QProcessEnvironment(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QProcessEnvironment _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QProcessEnvironment _q_arg0 = qscriptvalue_cast<QProcessEnvironment>(context->argument(0));
        QProcessEnvironment _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QProcessEnvironment _q_result = QProcessEnvironment::systemEnvironment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QProcessEnvironment_throw_ambiguity_error_helper(context,
        qtscript_QProcessEnvironment_function_names[_id],
        qtscript_QProcessEnvironment_function_signatures[_id]);
}

QScriptValue qtscript_create_QProcessEnvironment_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QProcessEnvironment*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QProcessEnvironment*)0));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QProcessEnvironment_prototype_call, qtscript_QProcessEnvironment_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QProcessEnvironment_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QProcessEnvironment>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QProcessEnvironment*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QProcessEnvironment_static_call, proto, qtscript_QProcessEnvironment_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QProcessEnvironment_static_call,
            qtscript_QProcessEnvironment_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QProcessEnvironment_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
