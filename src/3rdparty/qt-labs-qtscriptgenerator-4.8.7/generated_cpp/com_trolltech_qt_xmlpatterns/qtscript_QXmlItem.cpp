#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractxmlnodemodel.h>
#include <QVariant>
#include <qabstractxmlnodemodel.h>

static const char * const qtscript_QXmlItem_function_names[] = {
    "QXmlItem"
    // static
    // prototype
    , "isAtomicValue"
    , "isNode"
    , "isNull"
    , "toAtomicValue"
    , "toNodeModelIndex"
    , "toString"
};

static const char * const qtscript_QXmlItem_function_signatures[] = {
    "\nObject atomicValue\nQXmlItem other\nQXmlNodeModelIndex node"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QXmlItem_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QXmlItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlItem*)
Q_DECLARE_METATYPE(QXmlNodeModelIndex)

//
// QXmlItem
//

static QScriptValue qtscript_QXmlItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlItem* _q_self = qscriptvalue_cast<QXmlItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlItem.%0(): this object is not a QXmlItem")
            .arg(qtscript_QXmlItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAtomicValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNode();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->toAtomicValue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QXmlNodeModelIndex _q_result = _q_self->toNodeModelIndex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QXmlItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlItem_throw_ambiguity_error_helper(context,
        qtscript_QXmlItem_function_names[_id+1],
        qtscript_QXmlItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlItem _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (true) {
            QVariant _q_arg0 = context->argument(0).toVariant();
            QXmlItem _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QXmlItem>() == context->argument(0).toVariant().userType())) {
            QXmlItem _q_arg0 = qscriptvalue_cast<QXmlItem>(context->argument(0));
            QXmlItem _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QXmlNodeModelIndex>() == context->argument(0).toVariant().userType())) {
            QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
            QXmlItem _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlItem_throw_ambiguity_error_helper(context,
        qtscript_QXmlItem_function_names[_id],
        qtscript_QXmlItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlItem*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlItem_prototype_call, qtscript_QXmlItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlItem>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlItem_static_call, proto, qtscript_QXmlItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
