#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>
#include <qmimedata.h>
#include <qpoint.h>
#include <qrect.h>
#include <qwidget.h>

#include "qtscriptshell_QDragMoveEvent.h"

static const char * const qtscript_QDragMoveEvent_function_names[] = {
    "QDragMoveEvent"
    // static
    // prototype
    , "accept"
    , "answerRect"
    , "ignore"
    , "toString"
};

static const char * const qtscript_QDragMoveEvent_function_signatures[] = {
    "QPoint pos, DropActions actions, QMimeData data, MouseButtons buttons, KeyboardModifiers modifiers, Type type"
    // static
    // prototype
    , "QRect r"
    , ""
    , "QRect r"
""
};

static const int qtscript_QDragMoveEvent_function_lengths[] = {
    6
    // static
    // prototype
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QDragMoveEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDragMoveEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDragMoveEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QDragMoveEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QDropEvent*)

//
// QDragMoveEvent
//

static QScriptValue qtscript_QDragMoveEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDragMoveEvent* _q_self = qscriptvalue_cast<QDragMoveEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDragMoveEvent.%0(): this object is not a QDragMoveEvent")
            .arg(qtscript_QDragMoveEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->accept(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->answerRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->ignore(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QDragMoveEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragMoveEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragMoveEvent_function_names[_id+1],
        qtscript_QDragMoveEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDragMoveEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDragMoveEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 5) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QFlags<Qt::DropAction> _q_arg1 = qscriptvalue_cast<QFlags<Qt::DropAction> >(context->argument(1));
        QMimeData* _q_arg2 = qscriptvalue_cast<QMimeData*>(context->argument(2));
        QFlags<Qt::MouseButton> _q_arg3 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(3));
        QFlags<Qt::KeyboardModifier> _q_arg4 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(4));
        QtScriptShell_QDragMoveEvent* _q_cpp_result = new QtScriptShell_QDragMoveEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDragMoveEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 6) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QFlags<Qt::DropAction> _q_arg1 = qscriptvalue_cast<QFlags<Qt::DropAction> >(context->argument(1));
        QMimeData* _q_arg2 = qscriptvalue_cast<QMimeData*>(context->argument(2));
        QFlags<Qt::MouseButton> _q_arg3 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(3));
        QFlags<Qt::KeyboardModifier> _q_arg4 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(4));
        QEvent::Type _q_arg5 = qscriptvalue_cast<QEvent::Type>(context->argument(5));
        QtScriptShell_QDragMoveEvent* _q_cpp_result = new QtScriptShell_QDragMoveEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDragMoveEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragMoveEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragMoveEvent_function_names[_id],
        qtscript_QDragMoveEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QDragMoveEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDragMoveEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDragMoveEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDropEvent*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDragMoveEvent_prototype_call, qtscript_QDragMoveEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDragMoveEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDragMoveEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDragMoveEvent_static_call, proto, qtscript_QDragMoveEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
