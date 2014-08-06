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
#include <qtextstream.h>

static const char * const qtscript_QDomEntity_function_names[] = {
    "QDomEntity"
    // static
    // prototype
    , "notationName"
    , "publicId"
    , "systemId"
    , "toString"
};

static const char * const qtscript_QDomEntity_function_signatures[] = {
    "\nQDomEntity x"
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_QDomEntity_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QDomEntity_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomEntity::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomEntity)
Q_DECLARE_METATYPE(QDomEntity*)
Q_DECLARE_METATYPE(QDomNode*)

//
// QDomEntity
//

static QScriptValue qtscript_QDomEntity_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDomEntity* _q_self = qscriptvalue_cast<QDomEntity*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomEntity.%0(): this object is not a QDomEntity")
            .arg(qtscript_QDomEntity_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->notationName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->publicId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->systemId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QDomEntity");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomEntity_throw_ambiguity_error_helper(context,
        qtscript_QDomEntity_function_names[_id+1],
        qtscript_QDomEntity_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomEntity_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomEntity(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomEntity _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomEntity _q_arg0 = qscriptvalue_cast<QDomEntity>(context->argument(0));
        QDomEntity _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomEntity_throw_ambiguity_error_helper(context,
        qtscript_QDomEntity_function_names[_id],
        qtscript_QDomEntity_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomEntity_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomEntity*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomEntity*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDomNode*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomEntity_prototype_call, qtscript_QDomEntity_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomEntity_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomEntity>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomEntity*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomEntity_static_call, proto, qtscript_QDomEntity_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
