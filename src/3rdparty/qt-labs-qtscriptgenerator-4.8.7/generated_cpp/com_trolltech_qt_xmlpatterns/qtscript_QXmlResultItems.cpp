#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlresultitems.h>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qxmlresultitems.h>

#include "qtscriptshell_QXmlResultItems.h"

static const char * const qtscript_QXmlResultItems_function_names[] = {
    "QXmlResultItems"
    // static
    // prototype
    , "current"
    , "hasError"
    , "next"
    , "toString"
};

static const char * const qtscript_QXmlResultItems_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_QXmlResultItems_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QXmlResultItems_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlResultItems::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlResultItems*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlResultItems*)

//
// QXmlResultItems
//

static QScriptValue qtscript_QXmlResultItems_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlResultItems* _q_self = qscriptvalue_cast<QXmlResultItems*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlResultItems.%0(): this object is not a QXmlResultItems")
            .arg(qtscript_QXmlResultItems_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QXmlItem _q_result = _q_self->current();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasError();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QXmlItem _q_result = _q_self->next();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QXmlResultItems");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlResultItems_throw_ambiguity_error_helper(context,
        qtscript_QXmlResultItems_function_names[_id+1],
        qtscript_QXmlResultItems_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlResultItems_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlResultItems(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlResultItems* _q_cpp_result = new QtScriptShell_QXmlResultItems();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlResultItems*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlResultItems_throw_ambiguity_error_helper(context,
        qtscript_QXmlResultItems_function_names[_id],
        qtscript_QXmlResultItems_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlResultItems_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlResultItems*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlResultItems*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlResultItems_prototype_call, qtscript_QXmlResultItems_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlResultItems_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlResultItems*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlResultItems_static_call, proto, qtscript_QXmlResultItems_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
