#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qevent.h>
#include <QVariant>
#include <qcoreevent.h>

static const char * const qtscript_QDragLeaveEvent_function_names[] = {
    "QDragLeaveEvent"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QDragLeaveEvent_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QDragLeaveEvent_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QDragLeaveEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDragLeaveEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDragLeaveEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QDragLeaveEvent
//

static QScriptValue qtscript_QDragLeaveEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDragLeaveEvent* _q_self = qscriptvalue_cast<QDragLeaveEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDragLeaveEvent.%0(): this object is not a QDragLeaveEvent")
            .arg(qtscript_QDragLeaveEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QDragLeaveEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragLeaveEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragLeaveEvent_function_names[_id+1],
        qtscript_QDragLeaveEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDragLeaveEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDragLeaveEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDragLeaveEvent* _q_cpp_result = new QDragLeaveEvent();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragLeaveEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragLeaveEvent_function_names[_id],
        qtscript_QDragLeaveEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QDragLeaveEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDragLeaveEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDragLeaveEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));

    engine->setDefaultPrototype(qMetaTypeId<QDragLeaveEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDragLeaveEvent_static_call, proto, qtscript_QDragLeaveEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
