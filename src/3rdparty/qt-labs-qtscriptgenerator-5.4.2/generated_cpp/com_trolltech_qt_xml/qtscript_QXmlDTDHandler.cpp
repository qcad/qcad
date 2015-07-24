#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxml.h>
#include <QVariant>

#include "qtscriptshell_QXmlDTDHandler.h"

static const char * const qtscript_QXmlDTDHandler_function_names[] = {
    "QXmlDTDHandler"
    // static
    // prototype
    , "errorString"
    , "notationDecl"
    , "unparsedEntityDecl"
    , "toString"
};

static const char * const qtscript_QXmlDTDHandler_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "String name, String publicId, String systemId"
    , "String name, String publicId, String systemId, String notationName"
""
};

static const int qtscript_QXmlDTDHandler_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 3
    , 4
    , 0
};

static QScriptValue qtscript_QXmlDTDHandler_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlDTDHandler::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlDTDHandler*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlDTDHandler*)

//
// QXmlDTDHandler
//

static QScriptValue qtscript_QXmlDTDHandler_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlDTDHandler* _q_self = qscriptvalue_cast<QXmlDTDHandler*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlDTDHandler.%0(): this object is not a QXmlDTDHandler")
            .arg(qtscript_QXmlDTDHandler_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        bool _q_result = _q_self->notationDecl(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        bool _q_result = _q_self->unparsedEntityDecl(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QXmlDTDHandler");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlDTDHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlDTDHandler_function_names[_id+1],
        qtscript_QXmlDTDHandler_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlDTDHandler_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlDTDHandler(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlDTDHandler* _q_cpp_result = new QtScriptShell_QXmlDTDHandler();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlDTDHandler*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlDTDHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlDTDHandler_function_names[_id],
        qtscript_QXmlDTDHandler_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlDTDHandler_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlDTDHandler*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlDTDHandler*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlDTDHandler_prototype_call, qtscript_QXmlDTDHandler_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlDTDHandler_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlDTDHandler*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlDTDHandler_static_call, proto, qtscript_QXmlDTDHandler_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
