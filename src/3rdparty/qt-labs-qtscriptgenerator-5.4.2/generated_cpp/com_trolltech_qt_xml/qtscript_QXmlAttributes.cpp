#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxml.h>
#include <QVariant>

#include "qtscriptshell_QXmlAttributes.h"

static const char * const qtscript_QXmlAttributes_function_names[] = {
    "QXmlAttributes"
    // static
    // prototype
    , "append"
    , "clear"
    , "count"
    , "index"
    , "length"
    , "localName"
    , "qName"
    , "type"
    , "uri"
    , "value"
    , "toString"
};

static const char * const qtscript_QXmlAttributes_function_signatures[] = {
    ""
    // static
    // prototype
    , "String qName, String uri, String localPart, String value"
    , ""
    , ""
    , "String qName\nString uri, String localPart"
    , ""
    , "int index"
    , "int index"
    , "String qName\nString uri, String localName\nint index"
    , "int index"
    , "String qName\nString uri, String localName\nint index"
""
};

static const int qtscript_QXmlAttributes_function_lengths[] = {
    0
    // static
    // prototype
    , 4
    , 0
    , 0
    , 2
    , 0
    , 1
    , 1
    , 2
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QXmlAttributes_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlAttributes::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlAttributes)
Q_DECLARE_METATYPE(QXmlAttributes*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlAttributes)
Q_DECLARE_METATYPE(QtScriptShell_QXmlAttributes*)

//
// QXmlAttributes
//

static QScriptValue qtscript_QXmlAttributes_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlAttributes* _q_self = qscriptvalue_cast<QXmlAttributes*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlAttributes.%0(): this object is not a QXmlAttributes")
            .arg(qtscript_QXmlAttributes_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        _q_self->append(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->index(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->index(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->localName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->qName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_result = _q_self->type(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_result = _q_self->type(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = _q_self->type(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->uri(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_result = _q_self->value(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_result = _q_self->value(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = _q_self->value(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QXmlAttributes");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlAttributes_throw_ambiguity_error_helper(context,
        qtscript_QXmlAttributes_function_names[_id+1],
        qtscript_QXmlAttributes_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlAttributes_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlAttributes(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlAttributes _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlAttributes)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlAttributes_throw_ambiguity_error_helper(context,
        qtscript_QXmlAttributes_function_names[_id],
        qtscript_QXmlAttributes_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlAttributes_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlAttributes*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlAttributes*)0));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlAttributes_prototype_call, qtscript_QXmlAttributes_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlAttributes_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlAttributes>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlAttributes*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlAttributes_static_call, proto, qtscript_QXmlAttributes_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
