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

#include "qtscriptshell_QXmlContentHandler.h"

static const char * const qtscript_QXmlContentHandler_function_names[] = {
    "QXmlContentHandler"
    // static
    // prototype
    , "characters"
    , "endDocument"
    , "endElement"
    , "endPrefixMapping"
    , "errorString"
    , "ignorableWhitespace"
    , "processingInstruction"
    , "setDocumentLocator"
    , "skippedEntity"
    , "startDocument"
    , "startElement"
    , "startPrefixMapping"
    , "toString"
};

static const char * const qtscript_QXmlContentHandler_function_signatures[] = {
    ""
    // static
    // prototype
    , "String ch"
    , ""
    , "String namespaceURI, String localName, String qName"
    , "String prefix"
    , ""
    , "String ch"
    , "String target, String data"
    , "QXmlLocator locator"
    , "String name"
    , ""
    , "String namespaceURI, String localName, String qName, QXmlAttributes atts"
    , "String prefix, String uri"
""
};

static const int qtscript_QXmlContentHandler_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 0
    , 3
    , 1
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
    , 4
    , 2
    , 0
};

static QScriptValue qtscript_QXmlContentHandler_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlContentHandler::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlContentHandler*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlContentHandler*)
Q_DECLARE_METATYPE(QXmlLocator*)
Q_DECLARE_METATYPE(QXmlAttributes)

//
// QXmlContentHandler
//

static QScriptValue qtscript_QXmlContentHandler_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlContentHandler* _q_self = qscriptvalue_cast<QXmlContentHandler*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlContentHandler.%0(): this object is not a QXmlContentHandler")
            .arg(qtscript_QXmlContentHandler_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->characters(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->endDocument();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        bool _q_result = _q_self->endElement(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->endPrefixMapping(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->ignorableWhitespace(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->processingInstruction(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QXmlLocator* _q_arg0 = qscriptvalue_cast<QXmlLocator*>(context->argument(0));
        _q_self->setDocumentLocator(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->skippedEntity(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->startDocument();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QXmlAttributes _q_arg3 = qscriptvalue_cast<QXmlAttributes>(context->argument(3));
        bool _q_result = _q_self->startElement(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->startPrefixMapping(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QXmlContentHandler");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlContentHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlContentHandler_function_names[_id+1],
        qtscript_QXmlContentHandler_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlContentHandler_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlContentHandler(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlContentHandler* _q_cpp_result = new QtScriptShell_QXmlContentHandler();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlContentHandler*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlContentHandler_throw_ambiguity_error_helper(context,
        qtscript_QXmlContentHandler_function_names[_id],
        qtscript_QXmlContentHandler_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlContentHandler_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlContentHandler*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlContentHandler*)0));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlContentHandler_prototype_call, qtscript_QXmlContentHandler_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlContentHandler_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlContentHandler*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlContentHandler_static_call, proto, qtscript_QXmlContentHandler_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
