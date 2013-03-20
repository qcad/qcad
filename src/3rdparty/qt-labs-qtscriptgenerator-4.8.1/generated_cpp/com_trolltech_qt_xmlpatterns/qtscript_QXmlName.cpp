#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlname.h>
#include <QVariant>
#include <qxmlname.h>
#include <qxmlnamepool.h>

static const char * const qtscript_QXmlName_function_names[] = {
    "QXmlName"
    // static
    , "fromClarkName"
    , "isNCName"
    // prototype
    , "isNull"
    , "localName"
    , "namespaceUri"
    , "equals"
    , "prefix"
    , "toClarkName"
    , "toString"
};

static const char * const qtscript_QXmlName_function_signatures[] = {
    "\nQXmlNamePool namePool, String localName, String namespaceURI, String prefix"
    // static
    , "String clarkName, QXmlNamePool namePool"
    , "String candidate"
    // prototype
    , ""
    , "QXmlNamePool query"
    , "QXmlNamePool query"
    , "QXmlName other"
    , "QXmlNamePool query"
    , "QXmlNamePool query"
""
};

static const int qtscript_QXmlName_function_lengths[] = {
    4
    // static
    , 2
    , 1
    // prototype
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QXmlName_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlName::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlName*)
Q_DECLARE_METATYPE(QXmlNamePool)

//
// QXmlName
//

static QScriptValue qtscript_QXmlName_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlName* _q_self = qscriptvalue_cast<QXmlName*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlName.%0(): this object is not a QXmlName")
            .arg(qtscript_QXmlName_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QXmlNamePool _q_arg0 = qscriptvalue_cast<QXmlNamePool>(context->argument(0));
        QString _q_result = _q_self->localName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QXmlNamePool _q_arg0 = qscriptvalue_cast<QXmlNamePool>(context->argument(0));
        QString _q_result = _q_self->namespaceUri(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QXmlNamePool _q_arg0 = qscriptvalue_cast<QXmlNamePool>(context->argument(0));
        QString _q_result = _q_self->prefix(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QXmlNamePool _q_arg0 = qscriptvalue_cast<QXmlNamePool>(context->argument(0));
        QString _q_result = _q_self->toClarkName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QXmlName");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlName_throw_ambiguity_error_helper(context,
        qtscript_QXmlName_function_names[_id+3],
        qtscript_QXmlName_function_signatures[_id+3]);
}

static QScriptValue qtscript_QXmlName_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlName(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlName _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QXmlNamePool _q_arg0 = qscriptvalue_cast<QXmlNamePool>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QXmlName _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QXmlNamePool _q_arg1 = qscriptvalue_cast<QXmlNamePool>(context->argument(1));
        QXmlName _q_result = QXmlName::fromClarkName(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QXmlName::isNCName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlName_throw_ambiguity_error_helper(context,
        qtscript_QXmlName_function_names[_id],
        qtscript_QXmlName_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlName_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlName*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlName*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlName_prototype_call, qtscript_QXmlName_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlName_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlName>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlName*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlName_static_call, proto, qtscript_QXmlName_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlName_static_call,
            qtscript_QXmlName_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QXmlName_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
