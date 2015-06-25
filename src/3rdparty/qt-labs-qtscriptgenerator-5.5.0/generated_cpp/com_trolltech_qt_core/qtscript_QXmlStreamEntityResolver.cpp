#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxmlstream.h>
#include <QVariant>

#include "qtscriptshell_QXmlStreamEntityResolver.h"

static const char * const qtscript_QXmlStreamEntityResolver_function_names[] = {
    "QXmlStreamEntityResolver"
    // static
    // prototype
    , "resolveEntity"
    , "resolveUndeclaredEntity"
    , "toString"
};

static const char * const qtscript_QXmlStreamEntityResolver_function_signatures[] = {
    ""
    // static
    // prototype
    , "String publicId, String systemId"
    , "String name"
""
};

static const int qtscript_QXmlStreamEntityResolver_function_lengths[] = {
    0
    // static
    // prototype
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QXmlStreamEntityResolver_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlStreamEntityResolver::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlStreamEntityResolver*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlStreamEntityResolver*)

//
// QXmlStreamEntityResolver
//

static QScriptValue qtscript_QXmlStreamEntityResolver_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlStreamEntityResolver* _q_self = qscriptvalue_cast<QXmlStreamEntityResolver*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlStreamEntityResolver.%0(): this object is not a QXmlStreamEntityResolver")
            .arg(qtscript_QXmlStreamEntityResolver_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = _q_self->resolveEntity(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->resolveUndeclaredEntity(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QXmlStreamEntityResolver");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamEntityResolver_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamEntityResolver_function_names[_id+1],
        qtscript_QXmlStreamEntityResolver_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlStreamEntityResolver_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlStreamEntityResolver(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlStreamEntityResolver* _q_cpp_result = new QtScriptShell_QXmlStreamEntityResolver();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlStreamEntityResolver*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamEntityResolver_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamEntityResolver_function_names[_id],
        qtscript_QXmlStreamEntityResolver_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlStreamEntityResolver_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamEntityResolver*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlStreamEntityResolver*)0));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamEntityResolver_prototype_call, qtscript_QXmlStreamEntityResolver_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlStreamEntityResolver_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamEntityResolver*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlStreamEntityResolver_static_call, proto, qtscript_QXmlStreamEntityResolver_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
