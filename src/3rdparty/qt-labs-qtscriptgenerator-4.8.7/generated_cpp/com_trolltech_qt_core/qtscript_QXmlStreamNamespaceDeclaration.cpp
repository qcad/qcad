#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlstream.h>
#include <QVariant>
#include <qxmlstream.h>

static const char * const qtscript_QXmlStreamNamespaceDeclaration_function_names[] = {
    "QXmlStreamNamespaceDeclaration"
    // static
    // prototype
    , "namespaceUri"
    , "equals"
    , "prefix"
    , "toString"
};

static const char * const qtscript_QXmlStreamNamespaceDeclaration_function_signatures[] = {
    "\nString prefix, String namespaceUri\nQXmlStreamNamespaceDeclaration arg__1"
    // static
    // prototype
    , ""
    , "QXmlStreamNamespaceDeclaration other"
    , ""
""
};

static const int qtscript_QXmlStreamNamespaceDeclaration_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QXmlStreamNamespaceDeclaration_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlStreamNamespaceDeclaration::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlStreamNamespaceDeclaration)
Q_DECLARE_METATYPE(QXmlStreamNamespaceDeclaration*)
Q_DECLARE_METATYPE(QStringRef)

//
// QXmlStreamNamespaceDeclaration
//

static QScriptValue qtscript_QXmlStreamNamespaceDeclaration_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlStreamNamespaceDeclaration* _q_self = qscriptvalue_cast<QXmlStreamNamespaceDeclaration*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlStreamNamespaceDeclaration.%0(): this object is not a QXmlStreamNamespaceDeclaration")
            .arg(qtscript_QXmlStreamNamespaceDeclaration_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->namespaceUri();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QXmlStreamNamespaceDeclaration _q_arg0 = qscriptvalue_cast<QXmlStreamNamespaceDeclaration>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringRef _q_result = _q_self->prefix();
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QXmlStreamNamespaceDeclaration");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamNamespaceDeclaration_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamNamespaceDeclaration_function_names[_id+1],
        qtscript_QXmlStreamNamespaceDeclaration_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlStreamNamespaceDeclaration_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlStreamNamespaceDeclaration(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlStreamNamespaceDeclaration _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QXmlStreamNamespaceDeclaration _q_arg0 = qscriptvalue_cast<QXmlStreamNamespaceDeclaration>(context->argument(0));
        QXmlStreamNamespaceDeclaration _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QXmlStreamNamespaceDeclaration _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamNamespaceDeclaration_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamNamespaceDeclaration_function_names[_id],
        qtscript_QXmlStreamNamespaceDeclaration_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlStreamNamespaceDeclaration_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamNamespaceDeclaration*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlStreamNamespaceDeclaration*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamNamespaceDeclaration_prototype_call, qtscript_QXmlStreamNamespaceDeclaration_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlStreamNamespaceDeclaration_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamNamespaceDeclaration>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamNamespaceDeclaration*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlStreamNamespaceDeclaration_static_call, proto, qtscript_QXmlStreamNamespaceDeclaration_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
