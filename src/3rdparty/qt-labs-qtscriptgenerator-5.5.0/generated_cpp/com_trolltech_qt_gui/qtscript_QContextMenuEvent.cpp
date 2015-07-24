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
#include <qpoint.h>

#include "qtscriptshell_QContextMenuEvent.h"

static const char * const qtscript_QContextMenuEvent_function_names[] = {
    "QContextMenuEvent"
    // static
    // prototype
    , "globalPos"
    , "globalX"
    , "globalY"
    , "pos"
    , "reason"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QContextMenuEvent_function_signatures[] = {
    "Reason reason, QPoint pos\nReason reason, QPoint pos, QPoint globalPos\nReason reason, QPoint pos, QPoint globalPos, KeyboardModifiers modifiers"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QContextMenuEvent_function_lengths[] = {
    4
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
};

static QScriptValue qtscript_QContextMenuEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QContextMenuEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QContextMenuEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QContextMenuEvent*)
Q_DECLARE_METATYPE(QContextMenuEvent::Reason)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QInputEvent*)

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
// QContextMenuEvent::Reason
//

static const QContextMenuEvent::Reason qtscript_QContextMenuEvent_Reason_values[] = {
    QContextMenuEvent::Mouse
    , QContextMenuEvent::Keyboard
    , QContextMenuEvent::Other
};

static const char * const qtscript_QContextMenuEvent_Reason_keys[] = {
    "Mouse"
    , "Keyboard"
    , "Other"
};

static QString qtscript_QContextMenuEvent_Reason_toStringHelper(QContextMenuEvent::Reason value)
{
    if ((value >= QContextMenuEvent::Mouse) && (value <= QContextMenuEvent::Other))
        return qtscript_QContextMenuEvent_Reason_keys[static_cast<int>(value)-static_cast<int>(QContextMenuEvent::Mouse)];
    return QString();
}

static QScriptValue qtscript_QContextMenuEvent_Reason_toScriptValue(QScriptEngine *engine, const QContextMenuEvent::Reason &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QContextMenuEvent"));
    return clazz.property(qtscript_QContextMenuEvent_Reason_toStringHelper(value));
}

static void qtscript_QContextMenuEvent_Reason_fromScriptValue(const QScriptValue &value, QContextMenuEvent::Reason &out)
{
    out = qvariant_cast<QContextMenuEvent::Reason>(value.toVariant());
}

static QScriptValue qtscript_construct_QContextMenuEvent_Reason(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QContextMenuEvent::Mouse) && (arg <= QContextMenuEvent::Other))
        return qScriptValueFromValue(engine,  static_cast<QContextMenuEvent::Reason>(arg));
    return context->throwError(QString::fromLatin1("Reason(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QContextMenuEvent_Reason_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QContextMenuEvent::Reason value = qscriptvalue_cast<QContextMenuEvent::Reason>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QContextMenuEvent_Reason_toString(QScriptContext *context, QScriptEngine *engine)
{
    QContextMenuEvent::Reason value = qscriptvalue_cast<QContextMenuEvent::Reason>(context->thisObject());
    return QScriptValue(engine, qtscript_QContextMenuEvent_Reason_toStringHelper(value));
}

static QScriptValue qtscript_create_QContextMenuEvent_Reason_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QContextMenuEvent_Reason,
        qtscript_QContextMenuEvent_Reason_valueOf, qtscript_QContextMenuEvent_Reason_toString);
    qScriptRegisterMetaType<QContextMenuEvent::Reason>(engine, qtscript_QContextMenuEvent_Reason_toScriptValue,
        qtscript_QContextMenuEvent_Reason_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QContextMenuEvent_Reason_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QContextMenuEvent_Reason_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QContextMenuEvent
//

static QScriptValue qtscript_QContextMenuEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QContextMenuEvent* _q_self = qscriptvalue_cast<QContextMenuEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QContextMenuEvent.%0(): this object is not a QContextMenuEvent")
            .arg(qtscript_QContextMenuEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        const QPoint& _q_result = _q_self->globalPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->globalX();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->globalY();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        const QPoint& _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QContextMenuEvent::Reason _q_result = _q_self->reason();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->x();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->y();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QContextMenuEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QContextMenuEvent_throw_ambiguity_error_helper(context,
        qtscript_QContextMenuEvent_function_names[_id+1],
        qtscript_QContextMenuEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QContextMenuEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QContextMenuEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QContextMenuEvent::Reason _q_arg0 = qscriptvalue_cast<QContextMenuEvent::Reason>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QtScriptShell_QContextMenuEvent* _q_cpp_result = new QtScriptShell_QContextMenuEvent(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QContextMenuEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QContextMenuEvent::Reason _q_arg0 = qscriptvalue_cast<QContextMenuEvent::Reason>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QPoint _q_arg2 = qscriptvalue_cast<QPoint>(context->argument(2));
        QtScriptShell_QContextMenuEvent* _q_cpp_result = new QtScriptShell_QContextMenuEvent(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QContextMenuEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QContextMenuEvent::Reason _q_arg0 = qscriptvalue_cast<QContextMenuEvent::Reason>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QPoint _q_arg2 = qscriptvalue_cast<QPoint>(context->argument(2));
        QFlags<Qt::KeyboardModifier> _q_arg3 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(3));
        QtScriptShell_QContextMenuEvent* _q_cpp_result = new QtScriptShell_QContextMenuEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QContextMenuEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QContextMenuEvent_throw_ambiguity_error_helper(context,
        qtscript_QContextMenuEvent_function_names[_id],
        qtscript_QContextMenuEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QContextMenuEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QContextMenuEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QContextMenuEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QContextMenuEvent_prototype_call, qtscript_QContextMenuEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QContextMenuEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QContextMenuEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QContextMenuEvent_static_call, proto, qtscript_QContextMenuEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Reason"),
        qtscript_create_QContextMenuEvent_Reason_class(engine, ctor));
    return ctor;
}
