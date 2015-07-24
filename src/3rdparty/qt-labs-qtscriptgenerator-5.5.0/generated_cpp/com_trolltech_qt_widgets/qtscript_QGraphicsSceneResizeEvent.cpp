#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicssceneevent.h>
#include <QVariant>
#include <qgraphicssceneevent.h>
#include <qsize.h>
#include <qwidget.h>

static const char * const qtscript_QGraphicsSceneResizeEvent_function_names[] = {
    "QGraphicsSceneResizeEvent"
    // static
    // prototype
    , "newSize"
    , "oldSize"
    , "setNewSize"
    , "setOldSize"
    , "toString"
};

static const char * const qtscript_QGraphicsSceneResizeEvent_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , "QSizeF size"
    , "QSizeF size"
""
};

static const int qtscript_QGraphicsSceneResizeEvent_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsSceneResizeEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsSceneResizeEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsSceneResizeEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneEvent*)

//
// QGraphicsSceneResizeEvent
//

static QScriptValue qtscript_QGraphicsSceneResizeEvent_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsSceneResizeEvent* _q_self = qscriptvalue_cast<QGraphicsSceneResizeEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsSceneResizeEvent.%0(): this object is not a QGraphicsSceneResizeEvent")
            .arg(qtscript_QGraphicsSceneResizeEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->newSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->oldSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        _q_self->setNewSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        _q_self->setOldSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QGraphicsSceneResizeEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneResizeEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneResizeEvent_function_names[_id+1],
        qtscript_QGraphicsSceneResizeEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsSceneResizeEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsSceneResizeEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QGraphicsSceneResizeEvent* _q_cpp_result = new QGraphicsSceneResizeEvent();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneResizeEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneResizeEvent_function_names[_id],
        qtscript_QGraphicsSceneResizeEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsSceneResizeEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneResizeEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsSceneResizeEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsSceneEvent*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsSceneResizeEvent_prototype_call, qtscript_QGraphicsSceneResizeEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsSceneResizeEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneResizeEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsSceneResizeEvent_static_call, proto, qtscript_QGraphicsSceneResizeEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
