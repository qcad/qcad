#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlstream.h>
#include <QVariant>
#include <qxmlstream.h>

static const char * const qtscript_QXmlStreamEntityDeclaration_function_names[] = {
    "QXmlStreamEntityDeclaration"
    // static
    // prototype
    , "name"
    , "notationName"
    , "equals"
    , "publicId"
    , "systemId"
    , "value"
    , "toString"
};

static const char * const qtscript_QXmlStreamEntityDeclaration_function_signatures[] = {
    "\nQXmlStreamEntityDeclaration arg__1"
    // static
    // prototype
    , ""
    , ""
    , "QXmlStreamEntityDeclaration other"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QXmlStreamEntityDeclaration_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QXmlStreamEntityDeclaration_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlStreamEntityDeclaration::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlStreamEntityDeclaration)
Q_DECLARE_METATYPE(QXmlStreamEntityDeclaration*)
Q_DECLARE_METATYPE(QStringRef)

//
// QXmlStreamEntityDeclaration
//

static QScriptValue qtscript_QXmlStreamEntityDeclaration_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlStreamEntityDeclaration* _q_self = qscriptvalue_cast<QXmlStreamEntityDeclaration*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlStreamEntityDeclaration.%0(): this object is not a QXmlStreamEntityDeclaration")
            .arg(qtscript_QXmlStreamEntityDeclaration_function_names[_id+1]));
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
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->notationName();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QXmlStreamEntityDeclaration _q_arg0 = qscriptvalue_cast<QXmlStreamEntityDeclaration>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->publicId();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->systemId();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->value();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QXmlStreamEntityDeclaration");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamEntityDeclaration_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamEntityDeclaration_function_names[_id+1],
        qtscript_QXmlStreamEntityDeclaration_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlStreamEntityDeclaration_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlStreamEntityDeclaration(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlStreamEntityDeclaration _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QXmlStreamEntityDeclaration _q_arg0 = qscriptvalue_cast<QXmlStreamEntityDeclaration>(context->argument(0));
        QXmlStreamEntityDeclaration _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamEntityDeclaration_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamEntityDeclaration_function_names[_id],
        qtscript_QXmlStreamEntityDeclaration_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlStreamEntityDeclaration_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamEntityDeclaration*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlStreamEntityDeclaration*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamEntityDeclaration_prototype_call, qtscript_QXmlStreamEntityDeclaration_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlStreamEntityDeclaration_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamEntityDeclaration>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamEntityDeclaration*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlStreamEntityDeclaration_static_call, proto, qtscript_QXmlStreamEntityDeclaration_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
