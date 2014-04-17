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

#include "qtscriptshell_QXmlErrorHandler.h"

static const char * const qtscript_QXmlErrorHandler_function_names[] = {
    "QXmlErrorHandler"
    // static
    // prototype
    , "error"
    , "errorString"
    , "fatalError"
    , "warning"
    , "toString"
};

static const char * const qtscript_QXmlErrorHandler_function_signatures[] = {
    ""
    // static
    // prototype
    , "QXmlParseException exception"
    , ""
    , "QXmlParseException exception"
    , "QXmlParseException exception"
""
};

static const int qtscript_QXmlErrorHandler_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QXmlErrorHandler_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlErrorHandler::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlErrorHandler*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlErrorHandler*)
Q_DECLARE_METATYPE(QXmlParseException)

//
// QXmlErrorHandler
//

static QScriptValue qtscript_QXmlErrorHandler_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlErrorHandler* _q_self = qscriptvalue_cast<QXmlErrorHandler*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlErrorHandler.%0(): this object is not a QXmlErrorHandler")
            .arg(qtscript_QXmlErrorHandler_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QXmlParseException _q_arg0 = qscriptvalue_cast<QXmlParseException>(context->argument(0));
        bool _q_result = _q_self->error(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QXmlParseException _q_arg0 = qscriptvalue_cast<QXmlParseException>(context->argument(0));
        bool _q_result = _q_self->fatalError(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QXmlParseException _q_arg0 = qscriptvalue_cast<QXmlParseException>(context->argument(0));
        bool _q_result = _q_self->warning(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QXmlErrorHandler");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlErrorHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlErrorHandler_function_names[_id+1],
        qtscript_QXmlErrorHandler_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlErrorHandler_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlErrorHandler(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlErrorHandler* _q_cpp_result = new QtScriptShell_QXmlErrorHandler();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlErrorHandler*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlErrorHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlErrorHandler_function_names[_id],
        qtscript_QXmlErrorHandler_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlErrorHandler_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlErrorHandler*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlErrorHandler*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlErrorHandler_prototype_call, qtscript_QXmlErrorHandler_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlErrorHandler_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlErrorHandler*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlErrorHandler_static_call, proto, qtscript_QXmlErrorHandler_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
