#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicssceneevent.h>
#include <QVariant>
#include <qgraphicssceneevent.h>
#include <qmimedata.h>
#include <qpoint.h>
#include <qwidget.h>

static const char * const qtscript_QGraphicsSceneDragDropEvent_function_names[] = {
    "QGraphicsSceneDragDropEvent"
    // static
    // prototype
    , "acceptProposedAction"
    , "buttons"
    , "dropAction"
    , "mimeData"
    , "modifiers"
    , "pos"
    , "possibleActions"
    , "proposedAction"
    , "scenePos"
    , "screenPos"
    , "setButtons"
    , "setDropAction"
    , "setModifiers"
    , "setPos"
    , "setPossibleActions"
    , "setProposedAction"
    , "setScenePos"
    , "setScreenPos"
    , "source"
    , "toString"
};

static const char * const qtscript_QGraphicsSceneDragDropEvent_function_signatures[] = {
    "Type type"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "MouseButtons buttons"
    , "DropAction action"
    , "KeyboardModifiers modifiers"
    , "QPointF pos"
    , "DropActions actions"
    , "DropAction action"
    , "QPointF pos"
    , "QPoint pos"
    , ""
""
};

static const int qtscript_QGraphicsSceneDragDropEvent_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsSceneDragDropEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsSceneDragDropEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsSceneDragDropEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QGraphicsSceneEvent*)

//
// QGraphicsSceneDragDropEvent
//

static QScriptValue qtscript_QGraphicsSceneDragDropEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsSceneDragDropEvent* _q_self = qscriptvalue_cast<QGraphicsSceneDragDropEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsSceneDragDropEvent.%0(): this object is not a QGraphicsSceneDragDropEvent")
            .arg(qtscript_QGraphicsSceneDragDropEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->acceptProposedAction();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFlags<Qt::MouseButton> _q_result = _q_self->buttons();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        Qt::DropAction _q_result = _q_self->dropAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QMimeData* _q_result = const_cast<QMimeData*>(_q_self->mimeData());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QFlags<Qt::KeyboardModifier> _q_result = _q_self->modifiers();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DropAction> _q_result = _q_self->possibleActions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        Qt::DropAction _q_result = _q_self->proposedAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->scenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->screenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QFlags<Qt::MouseButton> _q_arg0 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(0));
        _q_self->setButtons(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        Qt::DropAction _q_arg0 = qscriptvalue_cast<Qt::DropAction>(context->argument(0));
        _q_self->setDropAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QFlags<Qt::KeyboardModifier> _q_arg0 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(0));
        _q_self->setModifiers(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QFlags<Qt::DropAction> _q_arg0 = qscriptvalue_cast<QFlags<Qt::DropAction> >(context->argument(0));
        _q_self->setPossibleActions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        Qt::DropAction _q_arg0 = qscriptvalue_cast<Qt::DropAction>(context->argument(0));
        _q_self->setProposedAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setScenePos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setScreenPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->source();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19: {
    QString result = QString::fromLatin1("QGraphicsSceneDragDropEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneDragDropEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneDragDropEvent_function_names[_id+1],
        qtscript_QGraphicsSceneDragDropEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsSceneDragDropEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsSceneDragDropEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QGraphicsSceneDragDropEvent* _q_cpp_result = new QGraphicsSceneDragDropEvent();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QGraphicsSceneDragDropEvent* _q_cpp_result = new QGraphicsSceneDragDropEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneDragDropEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneDragDropEvent_function_names[_id],
        qtscript_QGraphicsSceneDragDropEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsSceneDragDropEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneDragDropEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsSceneDragDropEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsSceneEvent*>()));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsSceneDragDropEvent_prototype_call, qtscript_QGraphicsSceneDragDropEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsSceneDragDropEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneDragDropEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsSceneDragDropEvent_static_call, proto, qtscript_QGraphicsSceneDragDropEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
