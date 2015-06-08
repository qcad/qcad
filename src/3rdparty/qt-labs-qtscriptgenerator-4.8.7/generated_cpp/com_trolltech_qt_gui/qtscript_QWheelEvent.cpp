#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qevent.h>
#include <QVariant>
#include <qpoint.h>

#include "qtscriptshell_QWheelEvent.h"

static const char * const qtscript_QWheelEvent_function_names[] = {
    "QWheelEvent"
    // static
    // prototype
    , "buttons"
    , "delta"
    , "globalPos"
    , "globalX"
    , "globalY"
    , "orientation"
    , "pos"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QWheelEvent_function_signatures[] = {
    "QPoint pos, QPoint globalPos, int delta, MouseButtons buttons, KeyboardModifiers modifiers, Orientation orient\nQPoint pos, int delta, MouseButtons buttons, KeyboardModifiers modifiers, Orientation orient"
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
""
};

static const int qtscript_QWheelEvent_function_lengths[] = {
    6
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
};

static QScriptValue qtscript_QWheelEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWheelEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWheelEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QWheelEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QInputEvent*)

//
// QWheelEvent
//

static QScriptValue qtscript_QWheelEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWheelEvent* _q_self = qscriptvalue_cast<QWheelEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWheelEvent.%0(): this object is not a QWheelEvent")
            .arg(qtscript_QWheelEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<Qt::MouseButton> _q_result = _q_self->buttons();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->delta();
        return QScriptValue(context->engine(), _q_result);
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
        Qt::Orientation _q_result = _q_self->orientation();
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
        int _q_result = _q_self->x();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->y();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QWheelEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWheelEvent_throw_ambiguity_error_helper(context,
        qtscript_QWheelEvent_function_names[_id+1],
        qtscript_QWheelEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWheelEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWheelEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 4) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::MouseButton> _q_arg2 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(2));
        QFlags<Qt::KeyboardModifier> _q_arg3 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(3));
        QtScriptShell_QWheelEvent* _q_cpp_result = new QtScriptShell_QWheelEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWheelEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())
            && context->argument(2).isNumber()
            && (qMetaTypeId<QFlags<Qt::MouseButton> >() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::KeyboardModifier> >() == context->argument(4).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            QFlags<Qt::MouseButton> _q_arg3 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(3));
            QFlags<Qt::KeyboardModifier> _q_arg4 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(4));
            QtScriptShell_QWheelEvent* _q_cpp_result = new QtScriptShell_QWheelEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWheelEvent*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<Qt::MouseButton> >() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::KeyboardModifier> >() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<Qt::Orientation>() == context->argument(4).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QFlags<Qt::MouseButton> _q_arg2 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(2));
            QFlags<Qt::KeyboardModifier> _q_arg3 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(3));
            Qt::Orientation _q_arg4 = qscriptvalue_cast<Qt::Orientation>(context->argument(4));
            QtScriptShell_QWheelEvent* _q_cpp_result = new QtScriptShell_QWheelEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWheelEvent*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 6) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QFlags<Qt::MouseButton> _q_arg3 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(3));
        QFlags<Qt::KeyboardModifier> _q_arg4 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(4));
        Qt::Orientation _q_arg5 = qscriptvalue_cast<Qt::Orientation>(context->argument(5));
        QtScriptShell_QWheelEvent* _q_cpp_result = new QtScriptShell_QWheelEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWheelEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWheelEvent_throw_ambiguity_error_helper(context,
        qtscript_QWheelEvent_function_names[_id],
        qtscript_QWheelEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QWheelEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWheelEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWheelEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent*>()));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWheelEvent_prototype_call, qtscript_QWheelEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWheelEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWheelEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWheelEvent_static_call, proto, qtscript_QWheelEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
