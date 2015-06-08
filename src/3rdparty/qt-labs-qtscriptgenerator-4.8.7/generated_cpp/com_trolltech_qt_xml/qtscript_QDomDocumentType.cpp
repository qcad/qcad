#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdom.h>
#include <QVariant>
#include <qdom.h>
#include <qtextstream.h>

static const char * const qtscript_QDomDocumentType_function_names[] = {
    "QDomDocumentType"
    // static
    // prototype
    , "entities"
    , "internalSubset"
    , "name"
    , "notations"
    , "publicId"
    , "systemId"
    , "toString"
};

static const char * const qtscript_QDomDocumentType_function_signatures[] = {
    "\nQDomDocumentType x"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QDomDocumentType_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QDomDocumentType_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomDocumentType::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomDocumentType)
Q_DECLARE_METATYPE(QDomDocumentType*)
Q_DECLARE_METATYPE(QDomNamedNodeMap)
Q_DECLARE_METATYPE(QDomNode*)

//
// QDomDocumentType
//

static QScriptValue qtscript_QDomDocumentType_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDomDocumentType* _q_self = qscriptvalue_cast<QDomDocumentType*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomDocumentType.%0(): this object is not a QDomDocumentType")
            .arg(qtscript_QDomDocumentType_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QDomNamedNodeMap _q_result = _q_self->entities();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->internalSubset();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QDomNamedNodeMap _q_result = _q_self->notations();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->publicId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->systemId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QDomDocumentType");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomDocumentType_throw_ambiguity_error_helper(context,
        qtscript_QDomDocumentType_function_names[_id+1],
        qtscript_QDomDocumentType_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomDocumentType_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomDocumentType(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomDocumentType _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomDocumentType _q_arg0 = qscriptvalue_cast<QDomDocumentType>(context->argument(0));
        QDomDocumentType _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomDocumentType_throw_ambiguity_error_helper(context,
        qtscript_QDomDocumentType_function_names[_id],
        qtscript_QDomDocumentType_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomDocumentType_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomDocumentType*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomDocumentType*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDomNode*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomDocumentType_prototype_call, qtscript_QDomDocumentType_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomDocumentType_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomDocumentType>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomDocumentType*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomDocumentType_static_call, proto, qtscript_QDomDocumentType_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
