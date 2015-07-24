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

#include "qtscriptshell_QXmlReader.h"

static const char * const qtscript_QXmlReader_function_names[] = {
    "QXmlReader"
    // static
    // prototype
    , "DTDHandler"
    , "contentHandler"
    , "declHandler"
    , "entityResolver"
    , "errorHandler"
    , "feature"
    , "hasFeature"
    , "hasProperty"
    , "lexicalHandler"
    , "parse"
    , "property"
    , "setContentHandler"
    , "setDTDHandler"
    , "setDeclHandler"
    , "setEntityResolver"
    , "setErrorHandler"
    , "setFeature"
    , "setLexicalHandler"
    , "setProperty"
    , "toString"
};

static const char * const qtscript_QXmlReader_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String name"
    , "String name"
    , "String name"
    , ""
    , "QXmlInputSource input\nQXmlInputSource input"
    , "String name"
    , "QXmlContentHandler handler"
    , "QXmlDTDHandler handler"
    , "QXmlDeclHandler handler"
    , "QXmlEntityResolver handler"
    , "QXmlErrorHandler handler"
    , "String name, bool value"
    , "QXmlLexicalHandler handler"
    , "String name, void value"
""
};

static const int qtscript_QXmlReader_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 0
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QXmlReader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlReader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlReader*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlReader*)
Q_DECLARE_METATYPE(QXmlDTDHandler*)
Q_DECLARE_METATYPE(QXmlContentHandler*)
Q_DECLARE_METATYPE(QXmlDeclHandler*)
Q_DECLARE_METATYPE(QXmlEntityResolver*)
Q_DECLARE_METATYPE(QXmlErrorHandler*)
Q_DECLARE_METATYPE(QXmlLexicalHandler*)
Q_DECLARE_METATYPE(QXmlInputSource)
Q_DECLARE_METATYPE(const QXmlInputSource*)

//
// QXmlReader
//

static QScriptValue qtscript_QXmlReader_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlReader* _q_self = qscriptvalue_cast<QXmlReader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlReader.%0(): this object is not a QXmlReader")
            .arg(qtscript_QXmlReader_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QXmlDTDHandler* _q_result = _q_self->DTDHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QXmlContentHandler* _q_result = _q_self->contentHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QXmlDeclHandler* _q_result = _q_self->declHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QXmlEntityResolver* _q_result = _q_self->entityResolver();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QXmlErrorHandler* _q_result = _q_self->errorHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->feature(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasFeature(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasProperty(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QXmlLexicalHandler* _q_result = _q_self->lexicalHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QXmlInputSource>() == context->argument(0).toVariant().userType())) {
            QXmlInputSource _q_arg0 = qscriptvalue_cast<QXmlInputSource>(context->argument(0));
            bool _q_result = _q_self->parse(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const QXmlInputSource*>(context->argument(0))) {
            const QXmlInputSource* _q_arg0 = qscriptvalue_cast<const QXmlInputSource*>(context->argument(0));
            bool _q_result = _q_self->parse(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        void* _q_result = _q_self->property(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QXmlContentHandler* _q_arg0 = qscriptvalue_cast<QXmlContentHandler*>(context->argument(0));
        _q_self->setContentHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QXmlDTDHandler* _q_arg0 = qscriptvalue_cast<QXmlDTDHandler*>(context->argument(0));
        _q_self->setDTDHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QXmlDeclHandler* _q_arg0 = qscriptvalue_cast<QXmlDeclHandler*>(context->argument(0));
        _q_self->setDeclHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QXmlEntityResolver* _q_arg0 = qscriptvalue_cast<QXmlEntityResolver*>(context->argument(0));
        _q_self->setEntityResolver(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QXmlErrorHandler* _q_arg0 = qscriptvalue_cast<QXmlErrorHandler*>(context->argument(0));
        _q_self->setErrorHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setFeature(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QXmlLexicalHandler* _q_arg0 = qscriptvalue_cast<QXmlLexicalHandler*>(context->argument(0));
        _q_self->setLexicalHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        void* _q_arg1 = qscriptvalue_cast<void*>(context->argument(1));
        _q_self->setProperty(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19: {
    QString result = QString::fromLatin1("QXmlReader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlReader_throw_ambiguity_error_helper(context,
        qtscript_QXmlReader_function_names[_id+1],
        qtscript_QXmlReader_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlReader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlReader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlReader* _q_cpp_result = new QtScriptShell_QXmlReader();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlReader*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlReader_throw_ambiguity_error_helper(context,
        qtscript_QXmlReader_function_names[_id],
        qtscript_QXmlReader_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlReader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlReader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlReader*)0));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlReader_prototype_call, qtscript_QXmlReader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlReader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlReader*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlReader_static_call, proto, qtscript_QXmlReader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
