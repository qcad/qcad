#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlserializer.h>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qabstractxmlreceiver.h>
#include <qiodevice.h>
#include <qtextcodec.h>
#include <qxmlname.h>
#include <qxmlquery.h>

#include "qtscriptshell_QXmlSerializer.h"

static const char * const qtscript_QXmlSerializer_function_names[] = {
    "QXmlSerializer"
    // static
    // prototype
    , "codec"
    , "outputDevice"
    , "setCodec"
    , "toString"
};

static const char * const qtscript_QXmlSerializer_function_signatures[] = {
    "QXmlQuery query, QIODevice outputDevice"
    // static
    // prototype
    , ""
    , ""
    , "QTextCodec codec"
""
};

static const int qtscript_QXmlSerializer_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QXmlSerializer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlSerializer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlSerializer*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlSerializer*)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QXmlQuery)
Q_DECLARE_METATYPE(QAbstractXmlReceiver*)

//
// QXmlSerializer
//

static QScriptValue qtscript_QXmlSerializer_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlSerializer* _q_self = qscriptvalue_cast<QXmlSerializer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlSerializer.%0(): this object is not a QXmlSerializer")
            .arg(qtscript_QXmlSerializer_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextCodec* _q_result = const_cast<QTextCodec*>(_q_self->codec());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->outputDevice();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
        _q_self->setCodec(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QXmlSerializer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlSerializer_throw_ambiguity_error_helper(context,
        qtscript_QXmlSerializer_function_names[_id+1],
        qtscript_QXmlSerializer_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlSerializer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlSerializer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QXmlQuery _q_arg0 = qscriptvalue_cast<QXmlQuery>(context->argument(0));
        QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
        QtScriptShell_QXmlSerializer* _q_cpp_result = new QtScriptShell_QXmlSerializer(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlSerializer*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlSerializer_throw_ambiguity_error_helper(context,
        qtscript_QXmlSerializer_function_names[_id],
        qtscript_QXmlSerializer_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlSerializer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlSerializer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlSerializer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractXmlReceiver*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlSerializer_prototype_call, qtscript_QXmlSerializer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlSerializer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlSerializer*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlSerializer_static_call, proto, qtscript_QXmlSerializer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
