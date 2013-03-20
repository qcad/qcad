#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>
#include <qpoint.h>

#include "qtscriptshell_QMoveEvent.h"

static const char * const qtscript_QMoveEvent_function_names[] = {
    "QMoveEvent"
    // static
    // prototype
    , "oldPos"
    , "pos"
    , "toString"
};

static const char * const qtscript_QMoveEvent_function_signatures[] = {
    "QPoint pos, QPoint oldPos"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QMoveEvent_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QMoveEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMoveEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMoveEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QMoveEvent*)
Q_DECLARE_METATYPE(QEvent*)

//
// QMoveEvent
//

static QScriptValue qtscript_QMoveEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QMoveEvent* _q_self = qscriptvalue_cast<QMoveEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMoveEvent.%0(): this object is not a QMoveEvent")
            .arg(qtscript_QMoveEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->oldPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QMoveEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMoveEvent_throw_ambiguity_error_helper(context,
        qtscript_QMoveEvent_function_names[_id+1],
        qtscript_QMoveEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMoveEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMoveEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QtScriptShell_QMoveEvent* _q_cpp_result = new QtScriptShell_QMoveEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QMoveEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMoveEvent_throw_ambiguity_error_helper(context,
        qtscript_QMoveEvent_function_names[_id],
        qtscript_QMoveEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QMoveEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMoveEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMoveEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMoveEvent_prototype_call, qtscript_QMoveEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMoveEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QMoveEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMoveEvent_static_call, proto, qtscript_QMoveEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
