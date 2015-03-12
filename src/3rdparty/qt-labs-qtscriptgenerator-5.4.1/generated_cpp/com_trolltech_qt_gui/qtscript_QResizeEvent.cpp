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
#include <qsize.h>

#include "qtscriptshell_QResizeEvent.h"

static const char * const qtscript_QResizeEvent_function_names[] = {
    "QResizeEvent"
    // static
    // prototype
    , "oldSize"
    , "size"
    , "toString"
};

static const char * const qtscript_QResizeEvent_function_signatures[] = {
    "QSize size, QSize oldSize"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QResizeEvent_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QResizeEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QResizeEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QResizeEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QResizeEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QResizeEvent
//

static QScriptValue qtscript_QResizeEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QResizeEvent* _q_self = qscriptvalue_cast<QResizeEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QResizeEvent.%0(): this object is not a QResizeEvent")
            .arg(qtscript_QResizeEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        const QSize& _q_result = _q_self->oldSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        const QSize& _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QResizeEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QResizeEvent_throw_ambiguity_error_helper(context,
        qtscript_QResizeEvent_function_names[_id+1],
        qtscript_QResizeEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QResizeEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QResizeEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        QtScriptShell_QResizeEvent* _q_cpp_result = new QtScriptShell_QResizeEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QResizeEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QResizeEvent_throw_ambiguity_error_helper(context,
        qtscript_QResizeEvent_function_names[_id],
        qtscript_QResizeEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QResizeEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QResizeEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QResizeEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QResizeEvent_prototype_call, qtscript_QResizeEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QResizeEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QResizeEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QResizeEvent_static_call, proto, qtscript_QResizeEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
