#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmouseeventtransition.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qabstractstate.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmouseeventtransition.h>
#include <qobject.h>
#include <qpainterpath.h>
#include <qstate.h>
#include <qstatemachine.h>

#include "qtscriptshell_QMouseEventTransition.h"

static const char * const qtscript_QMouseEventTransition_function_names[] = {
    "QMouseEventTransition"
    // static
    // prototype
    , "hitTestPath"
    , "setHitTestPath"
    , "toString"
};

static const char * const qtscript_QMouseEventTransition_function_signatures[] = {
    "QObject object, Type type, MouseButton button, QState sourceState\nQState sourceState"
    // static
    // prototype
    , ""
    , "QPainterPath path"
""
};

static const int qtscript_QMouseEventTransition_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QMouseEventTransition_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMouseEventTransition::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMouseEventTransition*)
Q_DECLARE_METATYPE(QtScriptShell_QMouseEventTransition*)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(Qt::MouseButton)
Q_DECLARE_METATYPE(QState*)
Q_DECLARE_METATYPE(QEventTransition*)

//
// QMouseEventTransition
//

static QScriptValue qtscript_QMouseEventTransition_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMouseEventTransition* _q_self = qscriptvalue_cast<QMouseEventTransition*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMouseEventTransition.%0(): this object is not a QMouseEventTransition")
            .arg(qtscript_QMouseEventTransition_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->hitTestPath();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->setHitTestPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QMouseEventTransition");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMouseEventTransition_throw_ambiguity_error_helper(context,
        qtscript_QMouseEventTransition_function_names[_id+1],
        qtscript_QMouseEventTransition_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMouseEventTransition_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMouseEventTransition(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMouseEventTransition* _q_cpp_result = new QtScriptShell_QMouseEventTransition();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMouseEventTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QState* _q_arg0 = qscriptvalue_cast<QState*>(context->argument(0));
        QtScriptShell_QMouseEventTransition* _q_cpp_result = new QtScriptShell_QMouseEventTransition(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMouseEventTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent::Type _q_arg1 = qscriptvalue_cast<QEvent::Type>(context->argument(1));
        Qt::MouseButton _q_arg2 = qscriptvalue_cast<Qt::MouseButton>(context->argument(2));
        QtScriptShell_QMouseEventTransition* _q_cpp_result = new QtScriptShell_QMouseEventTransition(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMouseEventTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent::Type _q_arg1 = qscriptvalue_cast<QEvent::Type>(context->argument(1));
        Qt::MouseButton _q_arg2 = qscriptvalue_cast<Qt::MouseButton>(context->argument(2));
        QState* _q_arg3 = qscriptvalue_cast<QState*>(context->argument(3));
        QtScriptShell_QMouseEventTransition* _q_cpp_result = new QtScriptShell_QMouseEventTransition(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMouseEventTransition*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMouseEventTransition_throw_ambiguity_error_helper(context,
        qtscript_QMouseEventTransition_function_names[_id],
        qtscript_QMouseEventTransition_function_signatures[_id]);
}

static QScriptValue qtscript_QMouseEventTransition_toScriptValue(QScriptEngine *engine, QMouseEventTransition* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMouseEventTransition_fromScriptValue(const QScriptValue &value, QMouseEventTransition* &out)
{
    out = qobject_cast<QMouseEventTransition*>(value.toQObject());
}

QScriptValue qtscript_create_QMouseEventTransition_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMouseEventTransition*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMouseEventTransition*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QEventTransition*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMouseEventTransition_prototype_call, qtscript_QMouseEventTransition_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMouseEventTransition_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMouseEventTransition*>(engine, qtscript_QMouseEventTransition_toScriptValue, 
        qtscript_QMouseEventTransition_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMouseEventTransition_static_call, proto, qtscript_QMouseEventTransition_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
