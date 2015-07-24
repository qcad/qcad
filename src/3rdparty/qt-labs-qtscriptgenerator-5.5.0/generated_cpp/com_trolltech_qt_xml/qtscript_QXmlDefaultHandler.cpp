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

#include "qtscriptshell_QXmlDefaultHandler.h"

static const char * const qtscript_QXmlDefaultHandler_function_names[] = {
    "QXmlDefaultHandler"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QXmlDefaultHandler_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QXmlDefaultHandler_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QXmlDefaultHandler_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlDefaultHandler::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlDefaultHandler*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlDefaultHandler*)
Q_DECLARE_METATYPE(QXmlContentHandler*)
Q_DECLARE_METATYPE(QXmlErrorHandler*)
Q_DECLARE_METATYPE(QXmlDTDHandler*)
Q_DECLARE_METATYPE(QXmlEntityResolver*)
Q_DECLARE_METATYPE(QXmlLexicalHandler*)
Q_DECLARE_METATYPE(QXmlDeclHandler*)

//
// QXmlDefaultHandler
//

static QScriptValue qtscript_QXmlDefaultHandler_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlDefaultHandler* _q_self = qscriptvalue_cast<QXmlDefaultHandler*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlDefaultHandler.%0(): this object is not a QXmlDefaultHandler")
            .arg(qtscript_QXmlDefaultHandler_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QXmlDefaultHandler");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlDefaultHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlDefaultHandler_function_names[_id+1],
        qtscript_QXmlDefaultHandler_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlDefaultHandler_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlDefaultHandler(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlDefaultHandler* _q_cpp_result = new QtScriptShell_QXmlDefaultHandler();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlDefaultHandler*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlDefaultHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlDefaultHandler_function_names[_id],
        qtscript_QXmlDefaultHandler_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlDefaultHandler_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlDefaultHandler*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlDefaultHandler*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QXmlContentHandler*>()));
    proto.setProperty(QString::fromLatin1("__QXmlErrorHandler__"),
        engine->defaultPrototype(qMetaTypeId<QXmlErrorHandler*>()),
        QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("__QXmlDTDHandler__"),
        engine->defaultPrototype(qMetaTypeId<QXmlDTDHandler*>()),
        QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("__QXmlEntityResolver__"),
        engine->defaultPrototype(qMetaTypeId<QXmlEntityResolver*>()),
        QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("__QXmlLexicalHandler__"),
        engine->defaultPrototype(qMetaTypeId<QXmlLexicalHandler*>()),
        QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("__QXmlDeclHandler__"),
        engine->defaultPrototype(qMetaTypeId<QXmlDeclHandler*>()),
        QScriptValue::SkipInEnumeration);

    engine->setDefaultPrototype(qMetaTypeId<QXmlDefaultHandler*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlDefaultHandler_static_call, proto, qtscript_QXmlDefaultHandler_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
