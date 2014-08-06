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

#include "qtscriptshell_QXmlSimpleReader.h"

static const char * const qtscript_QXmlSimpleReader_function_names[] = {
    "QXmlSimpleReader"
    // static
    // prototype
    , "parse"
    , "parseContinue"
    , "toString"
};

static const char * const qtscript_QXmlSimpleReader_function_signatures[] = {
    ""
    // static
    // prototype
    , "QXmlInputSource input, bool incremental"
    , ""
""
};

static const int qtscript_QXmlSimpleReader_function_lengths[] = {
    0
    // static
    // prototype
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QXmlSimpleReader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlSimpleReader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlSimpleReader*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlSimpleReader*)
Q_DECLARE_METATYPE(const QXmlInputSource*)
Q_DECLARE_METATYPE(QXmlReader*)

//
// QXmlSimpleReader
//

static QScriptValue qtscript_QXmlSimpleReader_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlSimpleReader* _q_self = qscriptvalue_cast<QXmlSimpleReader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlSimpleReader.%0(): this object is not a QXmlSimpleReader")
            .arg(qtscript_QXmlSimpleReader_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        const QXmlInputSource* _q_arg0 = qscriptvalue_cast<const QXmlInputSource*>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        bool _q_result = _q_self->parse(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->parseContinue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QXmlSimpleReader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlSimpleReader_throw_ambiguity_error_helper(context,
        qtscript_QXmlSimpleReader_function_names[_id+1],
        qtscript_QXmlSimpleReader_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlSimpleReader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlSimpleReader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlSimpleReader* _q_cpp_result = new QtScriptShell_QXmlSimpleReader();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlSimpleReader*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlSimpleReader_throw_ambiguity_error_helper(context,
        qtscript_QXmlSimpleReader_function_names[_id],
        qtscript_QXmlSimpleReader_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlSimpleReader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlSimpleReader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlSimpleReader*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QXmlReader*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlSimpleReader_prototype_call, qtscript_QXmlSimpleReader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlSimpleReader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlSimpleReader*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlSimpleReader_static_call, proto, qtscript_QXmlSimpleReader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
