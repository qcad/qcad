#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicssceneevent.h>
#include <QVariant>
#include <qgraphicssceneevent.h>
#include <qwidget.h>

static const char * const qtscript_QGraphicsSceneEvent_function_names[] = {
    "QGraphicsSceneEvent"
    // static
    // prototype
    , "widget"
    , "toString"
};

static const char * const qtscript_QGraphicsSceneEvent_function_signatures[] = {
    "Type type"
    // static
    // prototype
    , ""
""
};

static const int qtscript_QGraphicsSceneEvent_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsSceneEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsSceneEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsSceneEvent*)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QEvent*)

//
// QGraphicsSceneEvent
//

static QScriptValue qtscript_QGraphicsSceneEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsSceneEvent* _q_self = qscriptvalue_cast<QGraphicsSceneEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsSceneEvent.%0(): this object is not a QGraphicsSceneEvent")
            .arg(qtscript_QGraphicsSceneEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->widget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QGraphicsSceneEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneEvent_function_names[_id+1],
        qtscript_QGraphicsSceneEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsSceneEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsSceneEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QGraphicsSceneEvent* _q_cpp_result = new QGraphicsSceneEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneEvent_function_names[_id],
        qtscript_QGraphicsSceneEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsSceneEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsSceneEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEvent*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsSceneEvent_prototype_call, qtscript_QGraphicsSceneEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsSceneEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsSceneEvent_static_call, proto, qtscript_QGraphicsSceneEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
