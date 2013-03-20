#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxml.h>
#include <QVariant>
#include <qxml.h>

#include "qtscriptshell_QXmlEntityResolver.h"

static const char * const qtscript_QXmlEntityResolver_function_names[] = {
    "QXmlEntityResolver"
    // static
    // prototype
    , "errorString"
    , "resolveEntity"
    , "toString"
};

static const char * const qtscript_QXmlEntityResolver_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "String publicId, String systemId, QXmlInputSource ret"
""
};

static const int qtscript_QXmlEntityResolver_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 3
    , 0
};

static QScriptValue qtscript_QXmlEntityResolver_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlEntityResolver::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlEntityResolver*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlEntityResolver*)
Q_DECLARE_METATYPE(QXmlInputSource*)

//
// QXmlEntityResolver
//

static QScriptValue qtscript_QXmlEntityResolver_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlEntityResolver* _q_self = qscriptvalue_cast<QXmlEntityResolver*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlEntityResolver.%0(): this object is not a QXmlEntityResolver")
            .arg(qtscript_QXmlEntityResolver_function_names[_id+1]));
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
        QXmlInputSource* _q_arg2 = qscriptvalue_cast<QXmlInputSource*>(context->argument(2));
        bool _q_result = _q_self->resolveEntity(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QXmlEntityResolver");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlEntityResolver_throw_ambiguity_error_helper(context,
        qtscript_QXmlEntityResolver_function_names[_id+1],
        qtscript_QXmlEntityResolver_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlEntityResolver_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlEntityResolver(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlEntityResolver* _q_cpp_result = new QtScriptShell_QXmlEntityResolver();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlEntityResolver*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlEntityResolver_throw_ambiguity_error_helper(context,
        qtscript_QXmlEntityResolver_function_names[_id],
        qtscript_QXmlEntityResolver_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlEntityResolver_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlEntityResolver*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlEntityResolver*)0));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlEntityResolver_prototype_call, qtscript_QXmlEntityResolver_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlEntityResolver_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlEntityResolver*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlEntityResolver_static_call, proto, qtscript_QXmlEntityResolver_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
