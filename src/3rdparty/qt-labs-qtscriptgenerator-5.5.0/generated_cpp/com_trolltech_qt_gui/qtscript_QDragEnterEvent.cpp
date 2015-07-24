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
#include <qmimedata.h>
#include <qobject.h>
#include <qpoint.h>
#include <qrect.h>

static const char * const qtscript_QDragEnterEvent_function_names[] = {
    "QDragEnterEvent"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QDragEnterEvent_function_signatures[] = {
    "QPoint pos, DropActions actions, QMimeData data, MouseButtons buttons, KeyboardModifiers modifiers"
    // static
    // prototype
""
};

static const int qtscript_QDragEnterEvent_function_lengths[] = {
    5
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QDragEnterEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDragEnterEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDragEnterEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(const QMimeData*)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QDragMoveEvent*)

//
// QDragEnterEvent
//

static QScriptValue qtscript_QDragEnterEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDragEnterEvent* _q_self = qscriptvalue_cast<QDragEnterEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDragEnterEvent.%0(): this object is not a QDragEnterEvent")
            .arg(qtscript_QDragEnterEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QDragEnterEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragEnterEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragEnterEvent_function_names[_id+1],
        qtscript_QDragEnterEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDragEnterEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDragEnterEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 5) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QFlags<Qt::DropAction> _q_arg1 = qscriptvalue_cast<QFlags<Qt::DropAction> >(context->argument(1));
        const QMimeData* _q_arg2 = qscriptvalue_cast<const QMimeData*>(context->argument(2));
        QFlags<Qt::MouseButton> _q_arg3 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(3));
        QFlags<Qt::KeyboardModifier> _q_arg4 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(4));
        QDragEnterEvent* _q_cpp_result = new QDragEnterEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDragEnterEvent_throw_ambiguity_error_helper(context,
        qtscript_QDragEnterEvent_function_names[_id],
        qtscript_QDragEnterEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QDragEnterEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDragEnterEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDragEnterEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDragMoveEvent*>()));

    engine->setDefaultPrototype(qMetaTypeId<QDragEnterEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDragEnterEvent_static_call, proto, qtscript_QDragEnterEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
