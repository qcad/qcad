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

#include "qtscriptshell_QMouseEvent.h"

static const char * const qtscript_QMouseEvent_function_names[] = {
    "QMouseEvent"
    // static
    // prototype
    , "button"
    , "buttons"
    , "globalPos"
    , "globalX"
    , "globalY"
    , "localPos"
    , "pos"
    , "screenPos"
    , "windowPos"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QMouseEvent_function_signatures[] = {
    "Type type, QPointF localPos, MouseButton button, MouseButtons buttons, KeyboardModifiers modifiers\nType type, QPointF localPos, QPointF screenPos, MouseButton button, MouseButtons buttons, KeyboardModifiers modifiers\nType type, QPointF localPos, QPointF windowPos, QPointF screenPos, MouseButton button, MouseButtons buttons, KeyboardModifiers modifiers"
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
    , ""
""
};

static const int qtscript_QMouseEvent_function_lengths[] = {
    7
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
    , 0
    , 0
};

static QScriptValue qtscript_QMouseEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMouseEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMouseEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QMouseEvent*)
Q_DECLARE_METATYPE(Qt::MouseButton)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QInputEvent*)

//
// QMouseEvent
//

static QScriptValue qtscript_QMouseEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMouseEvent* _q_self = qscriptvalue_cast<QMouseEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMouseEvent.%0(): this object is not a QMouseEvent")
            .arg(qtscript_QMouseEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Qt::MouseButton _q_result = _q_self->button();
        return qScriptValueFromValue(context->engine(), _q_result);
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
        QPoint _q_result = _q_self->globalPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->globalX();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->globalY();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        const QPointF& _q_result = _q_self->localPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        const QPointF& _q_result = _q_self->screenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        const QPointF& _q_result = _q_self->windowPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->x();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->y();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11: {
    QString result = QString::fromLatin1("QMouseEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMouseEvent_throw_ambiguity_error_helper(context,
        qtscript_QMouseEvent_function_names[_id+1],
        qtscript_QMouseEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMouseEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMouseEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 5) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        Qt::MouseButton _q_arg2 = qscriptvalue_cast<Qt::MouseButton>(context->argument(2));
        QFlags<Qt::MouseButton> _q_arg3 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(3));
        QFlags<Qt::KeyboardModifier> _q_arg4 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(4));
        QtScriptShell_QMouseEvent* _q_cpp_result = new QtScriptShell_QMouseEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QMouseEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 6) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        QPointF _q_arg2 = qscriptvalue_cast<QPointF>(context->argument(2));
        Qt::MouseButton _q_arg3 = qscriptvalue_cast<Qt::MouseButton>(context->argument(3));
        QFlags<Qt::MouseButton> _q_arg4 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(4));
        QFlags<Qt::KeyboardModifier> _q_arg5 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(5));
        QtScriptShell_QMouseEvent* _q_cpp_result = new QtScriptShell_QMouseEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QMouseEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 7) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        QPointF _q_arg2 = qscriptvalue_cast<QPointF>(context->argument(2));
        QPointF _q_arg3 = qscriptvalue_cast<QPointF>(context->argument(3));
        Qt::MouseButton _q_arg4 = qscriptvalue_cast<Qt::MouseButton>(context->argument(4));
        QFlags<Qt::MouseButton> _q_arg5 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(5));
        QFlags<Qt::KeyboardModifier> _q_arg6 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(6));
        QtScriptShell_QMouseEvent* _q_cpp_result = new QtScriptShell_QMouseEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QMouseEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMouseEvent_throw_ambiguity_error_helper(context,
        qtscript_QMouseEvent_function_names[_id],
        qtscript_QMouseEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QMouseEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMouseEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMouseEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent*>()));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMouseEvent_prototype_call, qtscript_QMouseEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMouseEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QMouseEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMouseEvent_static_call, proto, qtscript_QMouseEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
