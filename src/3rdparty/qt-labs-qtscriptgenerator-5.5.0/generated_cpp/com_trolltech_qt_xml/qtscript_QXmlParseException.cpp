#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxml.h>
#include <QVariant>
#include <qxml.h>

static const char * const qtscript_QXmlParseException_function_names[] = {
    "QXmlParseException"
    // static
    // prototype
    , "columnNumber"
    , "lineNumber"
    , "message"
    , "publicId"
    , "systemId"
    , "toString"
};

static const char * const qtscript_QXmlParseException_function_signatures[] = {
    "String name, int c, int l, String p, String s\nQXmlParseException other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QXmlParseException_function_lengths[] = {
    5
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QXmlParseException_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlParseException::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlParseException)
Q_DECLARE_METATYPE(QXmlParseException*)

//
// QXmlParseException
//

static QScriptValue qtscript_QXmlParseException_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlParseException* _q_self = qscriptvalue_cast<QXmlParseException*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlParseException.%0(): this object is not a QXmlParseException")
            .arg(qtscript_QXmlParseException_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lineNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->message();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->publicId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->systemId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QXmlParseException");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlParseException_throw_ambiguity_error_helper(context,
        qtscript_QXmlParseException_function_names[_id+1],
        qtscript_QXmlParseException_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlParseException_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlParseException(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlParseException _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QXmlParseException _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QXmlParseException>() == context->argument(0).toVariant().userType())) {
            QXmlParseException _q_arg0 = qscriptvalue_cast<QXmlParseException>(context->argument(0));
            QXmlParseException _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QXmlParseException _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QXmlParseException _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QString _q_arg3 = context->argument(3).toString();
        QXmlParseException _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 5) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QString _q_arg3 = context->argument(3).toString();
        QString _q_arg4 = context->argument(4).toString();
        QXmlParseException _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlParseException_throw_ambiguity_error_helper(context,
        qtscript_QXmlParseException_function_names[_id],
        qtscript_QXmlParseException_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlParseException_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlParseException*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlParseException*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlParseException_prototype_call, qtscript_QXmlParseException_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlParseException_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlParseException>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlParseException*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlParseException_static_call, proto, qtscript_QXmlParseException_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
