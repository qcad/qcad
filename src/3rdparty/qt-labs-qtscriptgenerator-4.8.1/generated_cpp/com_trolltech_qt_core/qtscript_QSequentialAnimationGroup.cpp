#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsequentialanimationgroup.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpauseanimation.h>
#include <qsequentialanimationgroup.h>

#include "qtscriptshell_QSequentialAnimationGroup.h"

static const char * const qtscript_QSequentialAnimationGroup_function_names[] = {
    "QSequentialAnimationGroup"
    // static
    // prototype
    , "addPause"
    , "insertPause"
    , "toString"
};

static const char * const qtscript_QSequentialAnimationGroup_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "int msecs"
    , "int index, int msecs"
""
};

static const int qtscript_QSequentialAnimationGroup_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QSequentialAnimationGroup_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSequentialAnimationGroup::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSequentialAnimationGroup*)
Q_DECLARE_METATYPE(QtScriptShell_QSequentialAnimationGroup*)
Q_DECLARE_METATYPE(QPauseAnimation*)
Q_DECLARE_METATYPE(QAnimationGroup*)

//
// QSequentialAnimationGroup
//

static QScriptValue qtscript_QSequentialAnimationGroup_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSequentialAnimationGroup* _q_self = qscriptvalue_cast<QSequentialAnimationGroup*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSequentialAnimationGroup.%0(): this object is not a QSequentialAnimationGroup")
            .arg(qtscript_QSequentialAnimationGroup_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPauseAnimation* _q_result = _q_self->addPause(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QPauseAnimation* _q_result = _q_self->insertPause(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QSequentialAnimationGroup");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSequentialAnimationGroup_throw_ambiguity_error_helper(context,
        qtscript_QSequentialAnimationGroup_function_names[_id+1],
        qtscript_QSequentialAnimationGroup_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSequentialAnimationGroup_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSequentialAnimationGroup(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSequentialAnimationGroup* _q_cpp_result = new QtScriptShell_QSequentialAnimationGroup();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSequentialAnimationGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSequentialAnimationGroup* _q_cpp_result = new QtScriptShell_QSequentialAnimationGroup(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSequentialAnimationGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSequentialAnimationGroup_throw_ambiguity_error_helper(context,
        qtscript_QSequentialAnimationGroup_function_names[_id],
        qtscript_QSequentialAnimationGroup_function_signatures[_id]);
}

static QScriptValue qtscript_QSequentialAnimationGroup_toScriptValue(QScriptEngine *engine, QSequentialAnimationGroup* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSequentialAnimationGroup_fromScriptValue(const QScriptValue &value, QSequentialAnimationGroup* &out)
{
    out = qobject_cast<QSequentialAnimationGroup*>(value.toQObject());
}

QScriptValue qtscript_create_QSequentialAnimationGroup_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSequentialAnimationGroup*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSequentialAnimationGroup*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAnimationGroup*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSequentialAnimationGroup_prototype_call, qtscript_QSequentialAnimationGroup_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSequentialAnimationGroup_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSequentialAnimationGroup*>(engine, qtscript_QSequentialAnimationGroup_toScriptValue, 
        qtscript_QSequentialAnimationGroup_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSequentialAnimationGroup_static_call, proto, qtscript_QSequentialAnimationGroup_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
