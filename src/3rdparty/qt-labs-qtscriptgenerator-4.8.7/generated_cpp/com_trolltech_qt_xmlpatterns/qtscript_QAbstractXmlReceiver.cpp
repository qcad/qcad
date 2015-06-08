#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractxmlreceiver.h>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qabstractxmlreceiver.h>
#include <qxmlname.h>

#include "qtscriptshell_QAbstractXmlReceiver.h"

static const char * const qtscript_QAbstractXmlReceiver_function_names[] = {
    "QAbstractXmlReceiver"
    // static
    // prototype
    , "atomicValue"
    , "attribute"
    , "characters"
    , "comment"
    , "endDocument"
    , "endElement"
    , "endOfSequence"
    , "namespaceBinding"
    , "processingInstruction"
    , "startDocument"
    , "startElement"
    , "startOfSequence"
    , "whitespaceOnly"
    , "toString"
};

static const char * const qtscript_QAbstractXmlReceiver_function_signatures[] = {
    ""
    // static
    // prototype
    , "Object value"
    , "QXmlName name, String value"
    , "String value"
    , "String value"
    , ""
    , ""
    , ""
    , "QXmlName name"
    , "QXmlName target, String value"
    , ""
    , "QXmlName name"
    , ""
    , "String value"
""
};

static const int qtscript_QAbstractXmlReceiver_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 2
    , 0
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractXmlReceiver_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractXmlReceiver::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractXmlReceiver*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractXmlReceiver*)
Q_DECLARE_METATYPE(QStringRef)

//
// QAbstractXmlReceiver
//

static QScriptValue qtscript_QAbstractXmlReceiver_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractXmlReceiver* _q_self = qscriptvalue_cast<QAbstractXmlReceiver*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractXmlReceiver.%0(): this object is not a QAbstractXmlReceiver")
            .arg(qtscript_QAbstractXmlReceiver_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->atomicValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
        QStringRef _q_arg1 = qscriptvalue_cast<QStringRef>(context->argument(1));
        _q_self->attribute(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
        _q_self->characters(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->comment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->endDocument();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->endElement();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->endOfSequence();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
        _q_self->namespaceBinding(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->processingInstruction(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->startDocument();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
        _q_self->startElement(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        _q_self->startOfSequence();
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QStringRef _q_arg0 = qscriptvalue_cast<QStringRef>(context->argument(0));
        _q_self->whitespaceOnly(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QAbstractXmlReceiver");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractXmlReceiver_throw_ambiguity_error_helper(context,
        qtscript_QAbstractXmlReceiver_function_names[_id+1],
        qtscript_QAbstractXmlReceiver_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractXmlReceiver_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractXmlReceiver(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractXmlReceiver* _q_cpp_result = new QtScriptShell_QAbstractXmlReceiver();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAbstractXmlReceiver*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractXmlReceiver_throw_ambiguity_error_helper(context,
        qtscript_QAbstractXmlReceiver_function_names[_id],
        qtscript_QAbstractXmlReceiver_function_signatures[_id]);
}

QScriptValue qtscript_create_QAbstractXmlReceiver_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractXmlReceiver*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractXmlReceiver*)0));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractXmlReceiver_prototype_call, qtscript_QAbstractXmlReceiver_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractXmlReceiver_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAbstractXmlReceiver*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractXmlReceiver_static_call, proto, qtscript_QAbstractXmlReceiver_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
