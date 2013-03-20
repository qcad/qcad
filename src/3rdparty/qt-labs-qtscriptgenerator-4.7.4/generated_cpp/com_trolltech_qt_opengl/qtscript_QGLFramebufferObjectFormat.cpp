#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qglframebufferobject.h>
#include <QVariant>
#include <qglframebufferobject.h>

static const char * const qtscript_QGLFramebufferObjectFormat_function_names[] = {
    "QGLFramebufferObjectFormat"
    // static
    // prototype
    , "attachment"
    , "operator_assign"
    , "equals"
    , "samples"
    , "setAttachment"
    , "setSamples"
    , "toString"
};

static const char * const qtscript_QGLFramebufferObjectFormat_function_signatures[] = {
    "\nQGLFramebufferObjectFormat other"
    // static
    // prototype
    , ""
    , "QGLFramebufferObjectFormat other"
    , "QGLFramebufferObjectFormat other"
    , ""
    , "Attachment attachment"
    , "int samples"
""
};

static const int qtscript_QGLFramebufferObjectFormat_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QGLFramebufferObjectFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLFramebufferObjectFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLFramebufferObjectFormat)
Q_DECLARE_METATYPE(QGLFramebufferObjectFormat*)
Q_DECLARE_METATYPE(QGLFramebufferObject::Attachment)

//
// QGLFramebufferObjectFormat
//

static QScriptValue qtscript_QGLFramebufferObjectFormat_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGLFramebufferObjectFormat* _q_self = qscriptvalue_cast<QGLFramebufferObjectFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLFramebufferObjectFormat.%0(): this object is not a QGLFramebufferObjectFormat")
            .arg(qtscript_QGLFramebufferObjectFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QGLFramebufferObject::Attachment _q_result = _q_self->attachment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QGLFramebufferObjectFormat _q_arg0 = qscriptvalue_cast<QGLFramebufferObjectFormat>(context->argument(0));
        QGLFramebufferObjectFormat _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QGLFramebufferObjectFormat _q_arg0 = qscriptvalue_cast<QGLFramebufferObjectFormat>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->samples();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QGLFramebufferObject::Attachment _q_arg0 = qscriptvalue_cast<QGLFramebufferObject::Attachment>(context->argument(0));
        _q_self->setAttachment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setSamples(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QGLFramebufferObjectFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLFramebufferObjectFormat_throw_ambiguity_error_helper(context,
        qtscript_QGLFramebufferObjectFormat_function_names[_id+1],
        qtscript_QGLFramebufferObjectFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGLFramebufferObjectFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLFramebufferObjectFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QGLFramebufferObjectFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGLFramebufferObjectFormat _q_arg0 = qscriptvalue_cast<QGLFramebufferObjectFormat>(context->argument(0));
        QGLFramebufferObjectFormat _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLFramebufferObjectFormat_throw_ambiguity_error_helper(context,
        qtscript_QGLFramebufferObjectFormat_function_names[_id],
        qtscript_QGLFramebufferObjectFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QGLFramebufferObjectFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLFramebufferObjectFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLFramebufferObjectFormat*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLFramebufferObjectFormat_prototype_call, qtscript_QGLFramebufferObjectFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLFramebufferObjectFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGLFramebufferObjectFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QGLFramebufferObjectFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLFramebufferObjectFormat_static_call, proto, qtscript_QGLFramebufferObjectFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
