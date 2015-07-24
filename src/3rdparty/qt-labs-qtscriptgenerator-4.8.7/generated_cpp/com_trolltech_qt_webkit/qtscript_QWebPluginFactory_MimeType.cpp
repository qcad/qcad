#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwebpluginfactory.h>
#include <QVariant>
#include <qwebpluginfactory.h>

#include "qtscriptshell_QWebPluginFactory_MimeType.h"

static const char * const qtscript_QWebPluginFactory_MimeType_function_names[] = {
    "QWebPluginFactory_MimeType"
    // static
    // prototype
    , "equals"
    , "toString"
};

static const char * const qtscript_QWebPluginFactory_MimeType_function_signatures[] = {
    ""
    // static
    // prototype
    , "QWebPluginFactory_MimeType other"
""
};

static const int qtscript_QWebPluginFactory_MimeType_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QWebPluginFactory_MimeType_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebPluginFactory_MimeType::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebPluginFactory::MimeType)
Q_DECLARE_METATYPE(QWebPluginFactory::MimeType*)
Q_DECLARE_METATYPE(QtScriptShell_QWebPluginFactory_MimeType)
Q_DECLARE_METATYPE(QtScriptShell_QWebPluginFactory_MimeType*)

//
// QWebPluginFactory_MimeType
//

static QScriptValue qtscript_QWebPluginFactory_MimeType_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWebPluginFactory::MimeType* _q_self = qscriptvalue_cast<QWebPluginFactory::MimeType*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebPluginFactory_MimeType.%0(): this object is not a QWebPluginFactory_MimeType")
            .arg(qtscript_QWebPluginFactory_MimeType_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWebPluginFactory::MimeType _q_arg0 = qscriptvalue_cast<QWebPluginFactory::MimeType>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QWebPluginFactory_MimeType");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPluginFactory_MimeType_throw_ambiguity_error_helper(context,
        qtscript_QWebPluginFactory_MimeType_function_names[_id+1],
        qtscript_QWebPluginFactory_MimeType_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebPluginFactory_MimeType_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebPluginFactory_MimeType(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWebPluginFactory_MimeType _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWebPluginFactory::MimeType)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPluginFactory_MimeType_throw_ambiguity_error_helper(context,
        qtscript_QWebPluginFactory_MimeType_function_names[_id],
        qtscript_QWebPluginFactory_MimeType_function_signatures[_id]);
}

QScriptValue qtscript_create_QWebPluginFactory_MimeType_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebPluginFactory::MimeType*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebPluginFactory::MimeType*)0));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebPluginFactory_MimeType_prototype_call, qtscript_QWebPluginFactory_MimeType_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebPluginFactory_MimeType_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWebPluginFactory::MimeType>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QWebPluginFactory::MimeType*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebPluginFactory_MimeType_static_call, proto, qtscript_QWebPluginFactory_MimeType_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
