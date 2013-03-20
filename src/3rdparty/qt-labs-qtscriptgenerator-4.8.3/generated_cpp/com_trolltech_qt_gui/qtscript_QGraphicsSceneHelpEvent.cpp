#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicssceneevent.h>
#include <QVariant>
#include <qgraphicssceneevent.h>
#include <qpoint.h>
#include <qwidget.h>

static const char * const qtscript_QGraphicsSceneHelpEvent_function_names[] = {
    "QGraphicsSceneHelpEvent"
    // static
    // prototype
    , "scenePos"
    , "screenPos"
    , "setScenePos"
    , "setScreenPos"
    , "toString"
};

static const char * const qtscript_QGraphicsSceneHelpEvent_function_signatures[] = {
    "Type type"
    // static
    // prototype
    , ""
    , ""
    , "QPointF pos"
    , "QPoint pos"
""
};

static const int qtscript_QGraphicsSceneHelpEvent_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsSceneHelpEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsSceneHelpEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsSceneHelpEvent*)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QGraphicsSceneEvent*)

//
// QGraphicsSceneHelpEvent
//

static QScriptValue qtscript_QGraphicsSceneHelpEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsSceneHelpEvent* _q_self = qscriptvalue_cast<QGraphicsSceneHelpEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsSceneHelpEvent.%0(): this object is not a QGraphicsSceneHelpEvent")
            .arg(qtscript_QGraphicsSceneHelpEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->scenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->screenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setScenePos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setScreenPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QGraphicsSceneHelpEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneHelpEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneHelpEvent_function_names[_id+1],
        qtscript_QGraphicsSceneHelpEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsSceneHelpEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsSceneHelpEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QGraphicsSceneHelpEvent* _q_cpp_result = new QGraphicsSceneHelpEvent();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QGraphicsSceneHelpEvent* _q_cpp_result = new QGraphicsSceneHelpEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneHelpEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneHelpEvent_function_names[_id],
        qtscript_QGraphicsSceneHelpEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsSceneHelpEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneHelpEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsSceneHelpEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsSceneEvent*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsSceneHelpEvent_prototype_call, qtscript_QGraphicsSceneHelpEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsSceneHelpEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneHelpEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsSceneHelpEvent_static_call, proto, qtscript_QGraphicsSceneHelpEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
