#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxmlstream.h>
#include <QVariant>
#include <qxmlstream.h>

static const char * const qtscript_QXmlStreamNotationDeclaration_function_names[] = {
    "QXmlStreamNotationDeclaration"
    // static
    // prototype
    , "name"
    , "equals"
    , "publicId"
    , "systemId"
    , "toString"
};

static const char * const qtscript_QXmlStreamNotationDeclaration_function_signatures[] = {
    "\nQXmlStreamNotationDeclaration arg__1"
    // static
    // prototype
    , ""
    , "QXmlStreamNotationDeclaration other"
    , ""
    , ""
""
};

static const int qtscript_QXmlStreamNotationDeclaration_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QXmlStreamNotationDeclaration_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlStreamNotationDeclaration::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlStreamNotationDeclaration)
Q_DECLARE_METATYPE(QXmlStreamNotationDeclaration*)
Q_DECLARE_METATYPE(QStringRef)

//
// QXmlStreamNotationDeclaration
//

static QScriptValue qtscript_QXmlStreamNotationDeclaration_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlStreamNotationDeclaration* _q_self = qscriptvalue_cast<QXmlStreamNotationDeclaration*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlStreamNotationDeclaration.%0(): this object is not a QXmlStreamNotationDeclaration")
            .arg(qtscript_QXmlStreamNotationDeclaration_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->name();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QXmlStreamNotationDeclaration _q_arg0 = qscriptvalue_cast<QXmlStreamNotationDeclaration>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->publicId();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->systemId();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QXmlStreamNotationDeclaration");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamNotationDeclaration_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamNotationDeclaration_function_names[_id+1],
        qtscript_QXmlStreamNotationDeclaration_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlStreamNotationDeclaration_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlStreamNotationDeclaration(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlStreamNotationDeclaration _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QXmlStreamNotationDeclaration _q_arg0 = qscriptvalue_cast<QXmlStreamNotationDeclaration>(context->argument(0));
        QXmlStreamNotationDeclaration _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamNotationDeclaration_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamNotationDeclaration_function_names[_id],
        qtscript_QXmlStreamNotationDeclaration_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlStreamNotationDeclaration_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamNotationDeclaration*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlStreamNotationDeclaration*)0));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamNotationDeclaration_prototype_call, qtscript_QXmlStreamNotationDeclaration_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlStreamNotationDeclaration_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamNotationDeclaration>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamNotationDeclaration*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlStreamNotationDeclaration_static_call, proto, qtscript_QXmlStreamNotationDeclaration_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
