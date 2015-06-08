#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxml.h>
#include <QVariant>

#include "qtscriptshell_QXmlDeclHandler.h"

static const char * const qtscript_QXmlDeclHandler_function_names[] = {
    "QXmlDeclHandler"
    // static
    // prototype
    , "attributeDecl"
    , "errorString"
    , "externalEntityDecl"
    , "internalEntityDecl"
    , "toString"
};

static const char * const qtscript_QXmlDeclHandler_function_signatures[] = {
    ""
    // static
    // prototype
    , "String eName, String aName, String type, String valueDefault, String value"
    , ""
    , "String name, String publicId, String systemId"
    , "String name, String value"
""
};

static const int qtscript_QXmlDeclHandler_function_lengths[] = {
    0
    // static
    // prototype
    , 5
    , 0
    , 3
    , 2
    , 0
};

static QScriptValue qtscript_QXmlDeclHandler_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlDeclHandler::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlDeclHandler*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlDeclHandler*)

//
// QXmlDeclHandler
//

static QScriptValue qtscript_QXmlDeclHandler_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlDeclHandler* _q_self = qscriptvalue_cast<QXmlDeclHandler*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlDeclHandler.%0(): this object is not a QXmlDeclHandler")
            .arg(qtscript_QXmlDeclHandler_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 5) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString _q_arg4 = context->argument(4).toString();
        bool _q_result = _q_self->attributeDecl(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
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
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        bool _q_result = _q_self->externalEntityDecl(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->internalEntityDecl(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QXmlDeclHandler");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlDeclHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlDeclHandler_function_names[_id+1],
        qtscript_QXmlDeclHandler_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlDeclHandler_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlDeclHandler(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlDeclHandler* _q_cpp_result = new QtScriptShell_QXmlDeclHandler();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlDeclHandler*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlDeclHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlDeclHandler_function_names[_id],
        qtscript_QXmlDeclHandler_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlDeclHandler_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlDeclHandler*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlDeclHandler*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlDeclHandler_prototype_call, qtscript_QXmlDeclHandler_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlDeclHandler_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlDeclHandler*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlDeclHandler_static_call, proto, qtscript_QXmlDeclHandler_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
