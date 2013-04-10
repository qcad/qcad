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

static const char * const qtscript_QGraphicsSceneContextMenuEvent_function_names[] = {
    "QGraphicsSceneContextMenuEvent"
    // static
    // prototype
    , "modifiers"
    , "pos"
    , "reason"
    , "scenePos"
    , "screenPos"
    , "setModifiers"
    , "setPos"
    , "setReason"
    , "setScenePos"
    , "setScreenPos"
    , "toString"
};

static const char * const qtscript_QGraphicsSceneContextMenuEvent_function_signatures[] = {
    "Type type"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "KeyboardModifiers modifiers"
    , "QPointF pos"
    , "Reason reason"
    , "QPointF pos"
    , "QPoint pos"
""
};

static const int qtscript_QGraphicsSceneContextMenuEvent_function_lengths[] = {
    1
    // static
    // prototype
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
    , 0
};

static QScriptValue qtscript_QGraphicsSceneContextMenuEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsSceneContextMenuEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsSceneContextMenuEvent*)
Q_DECLARE_METATYPE(QGraphicsSceneContextMenuEvent::Reason)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QGraphicsSceneEvent*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QGraphicsSceneContextMenuEvent::Reason
//

static const QGraphicsSceneContextMenuEvent::Reason qtscript_QGraphicsSceneContextMenuEvent_Reason_values[] = {
    QGraphicsSceneContextMenuEvent::Mouse
    , QGraphicsSceneContextMenuEvent::Keyboard
    , QGraphicsSceneContextMenuEvent::Other
};

static const char * const qtscript_QGraphicsSceneContextMenuEvent_Reason_keys[] = {
    "Mouse"
    , "Keyboard"
    , "Other"
};

static QString qtscript_QGraphicsSceneContextMenuEvent_Reason_toStringHelper(QGraphicsSceneContextMenuEvent::Reason value)
{
    if ((value >= QGraphicsSceneContextMenuEvent::Mouse) && (value <= QGraphicsSceneContextMenuEvent::Other))
        return qtscript_QGraphicsSceneContextMenuEvent_Reason_keys[static_cast<int>(value)-static_cast<int>(QGraphicsSceneContextMenuEvent::Mouse)];
    return QString();
}

static QScriptValue qtscript_QGraphicsSceneContextMenuEvent_Reason_toScriptValue(QScriptEngine *engine, const QGraphicsSceneContextMenuEvent::Reason &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsSceneContextMenuEvent"));
    return clazz.property(qtscript_QGraphicsSceneContextMenuEvent_Reason_toStringHelper(value));
}

static void qtscript_QGraphicsSceneContextMenuEvent_Reason_fromScriptValue(const QScriptValue &value, QGraphicsSceneContextMenuEvent::Reason &out)
{
    out = qvariant_cast<QGraphicsSceneContextMenuEvent::Reason>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsSceneContextMenuEvent_Reason(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsSceneContextMenuEvent::Mouse) && (arg <= QGraphicsSceneContextMenuEvent::Other))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsSceneContextMenuEvent::Reason>(arg));
    return context->throwError(QString::fromLatin1("Reason(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsSceneContextMenuEvent_Reason_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsSceneContextMenuEvent::Reason value = qscriptvalue_cast<QGraphicsSceneContextMenuEvent::Reason>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsSceneContextMenuEvent_Reason_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsSceneContextMenuEvent::Reason value = qscriptvalue_cast<QGraphicsSceneContextMenuEvent::Reason>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsSceneContextMenuEvent_Reason_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsSceneContextMenuEvent_Reason_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsSceneContextMenuEvent_Reason,
        qtscript_QGraphicsSceneContextMenuEvent_Reason_valueOf, qtscript_QGraphicsSceneContextMenuEvent_Reason_toString);
    qScriptRegisterMetaType<QGraphicsSceneContextMenuEvent::Reason>(engine, qtscript_QGraphicsSceneContextMenuEvent_Reason_toScriptValue,
        qtscript_QGraphicsSceneContextMenuEvent_Reason_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsSceneContextMenuEvent_Reason_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsSceneContextMenuEvent_Reason_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsSceneContextMenuEvent
//

static QScriptValue qtscript_QGraphicsSceneContextMenuEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsSceneContextMenuEvent* _q_self = qscriptvalue_cast<QGraphicsSceneContextMenuEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsSceneContextMenuEvent.%0(): this object is not a QGraphicsSceneContextMenuEvent")
            .arg(qtscript_QGraphicsSceneContextMenuEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<Qt::KeyboardModifier> _q_result = _q_self->modifiers();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QGraphicsSceneContextMenuEvent::Reason _q_result = _q_self->reason();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->scenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->screenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QFlags<Qt::KeyboardModifier> _q_arg0 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(0));
        _q_self->setModifiers(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QGraphicsSceneContextMenuEvent::Reason _q_arg0 = qscriptvalue_cast<QGraphicsSceneContextMenuEvent::Reason>(context->argument(0));
        _q_self->setReason(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setScenePos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setScreenPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QGraphicsSceneContextMenuEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneContextMenuEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneContextMenuEvent_function_names[_id+1],
        qtscript_QGraphicsSceneContextMenuEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsSceneContextMenuEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsSceneContextMenuEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QGraphicsSceneContextMenuEvent* _q_cpp_result = new QGraphicsSceneContextMenuEvent();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QGraphicsSceneContextMenuEvent* _q_cpp_result = new QGraphicsSceneContextMenuEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneContextMenuEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneContextMenuEvent_function_names[_id],
        qtscript_QGraphicsSceneContextMenuEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsSceneContextMenuEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneContextMenuEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsSceneContextMenuEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsSceneEvent*>()));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsSceneContextMenuEvent_prototype_call, qtscript_QGraphicsSceneContextMenuEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsSceneContextMenuEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneContextMenuEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsSceneContextMenuEvent_static_call, proto, qtscript_QGraphicsSceneContextMenuEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Reason"),
        qtscript_create_QGraphicsSceneContextMenuEvent_Reason_class(engine, ctor));
    return ctor;
}
