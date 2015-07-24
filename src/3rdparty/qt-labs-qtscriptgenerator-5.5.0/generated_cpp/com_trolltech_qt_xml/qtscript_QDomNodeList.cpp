#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdom.h>
#include <QVariant>
#include <qdom.h>

static const char * const qtscript_QDomNodeList_function_names[] = {
    "QDomNodeList"
    // static
    // prototype
    , "at"
    , "count"
    , "isEmpty"
    , "item"
    , "length"
    , "equals"
    , "size"
    , "toString"
};

static const char * const qtscript_QDomNodeList_function_signatures[] = {
    "\nQDomNodeList arg__1"
    // static
    // prototype
    , "int index"
    , ""
    , ""
    , "int index"
    , ""
    , "QDomNodeList arg__1"
    , ""
""
};

static const int qtscript_QDomNodeList_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QDomNodeList_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomNodeList::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomNodeList)
Q_DECLARE_METATYPE(QDomNodeList*)
Q_DECLARE_METATYPE(QDomNode)

//
// QDomNodeList
//

static QScriptValue qtscript_QDomNodeList_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDomNodeList* _q_self = qscriptvalue_cast<QDomNodeList*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomNodeList.%0(): this object is not a QDomNodeList")
            .arg(qtscript_QDomNodeList_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QDomNode _q_result = _q_self->at(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QDomNode _q_result = _q_self->item(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
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
        QDomNodeList _q_arg0 = qscriptvalue_cast<QDomNodeList>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QDomNodeList");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomNodeList_throw_ambiguity_error_helper(context,
        qtscript_QDomNodeList_function_names[_id+1],
        qtscript_QDomNodeList_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomNodeList_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomNodeList(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomNodeList _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomNodeList _q_arg0 = qscriptvalue_cast<QDomNodeList>(context->argument(0));
        QDomNodeList _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomNodeList_throw_ambiguity_error_helper(context,
        qtscript_QDomNodeList_function_names[_id],
        qtscript_QDomNodeList_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomNodeList_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomNodeList*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomNodeList*)0));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomNodeList_prototype_call, qtscript_QDomNodeList_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomNodeList_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomNodeList>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomNodeList*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomNodeList_static_call, proto, qtscript_QDomNodeList_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
