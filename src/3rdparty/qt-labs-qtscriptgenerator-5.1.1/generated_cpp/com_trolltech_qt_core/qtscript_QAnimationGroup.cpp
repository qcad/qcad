#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qanimationgroup.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QAnimationGroup.h"

static const char * const qtscript_QAnimationGroup_function_names[] = {
    "QAnimationGroup"
    // static
    // prototype
    , "addAnimation"
    , "animationAt"
    , "animationCount"
    , "clear"
    , "indexOfAnimation"
    , "insertAnimation"
    , "removeAnimation"
    , "takeAnimation"
    , "toString"
};

static const char * const qtscript_QAnimationGroup_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QAbstractAnimation animation"
    , "int index"
    , ""
    , ""
    , "QAbstractAnimation animation"
    , "int index, QAbstractAnimation animation"
    , "QAbstractAnimation animation"
    , "int index"
""
};

static const int qtscript_QAnimationGroup_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 0
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAnimationGroup_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAnimationGroup::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAnimationGroup*)
Q_DECLARE_METATYPE(QtScriptShell_QAnimationGroup*)
Q_DECLARE_METATYPE(QAbstractAnimation*)

//
// QAnimationGroup
//

static QScriptValue qtscript_QAnimationGroup_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAnimationGroup* _q_self = qscriptvalue_cast<QAnimationGroup*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAnimationGroup.%0(): this object is not a QAnimationGroup")
            .arg(qtscript_QAnimationGroup_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QAbstractAnimation* _q_arg0 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(0));
        _q_self->addAnimation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractAnimation* _q_result = _q_self->animationAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->animationCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QAbstractAnimation* _q_arg0 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(0));
        int _q_result = _q_self->indexOfAnimation(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractAnimation* _q_arg1 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(1));
        _q_self->insertAnimation(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QAbstractAnimation* _q_arg0 = qscriptvalue_cast<QAbstractAnimation*>(context->argument(0));
        _q_self->removeAnimation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractAnimation* _q_result = _q_self->takeAnimation(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QAnimationGroup");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAnimationGroup_throw_ambiguity_error_helper(context,
        qtscript_QAnimationGroup_function_names[_id+1],
        qtscript_QAnimationGroup_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAnimationGroup_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAnimationGroup(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAnimationGroup* _q_cpp_result = new QtScriptShell_QAnimationGroup();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAnimationGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAnimationGroup* _q_cpp_result = new QtScriptShell_QAnimationGroup(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAnimationGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAnimationGroup_throw_ambiguity_error_helper(context,
        qtscript_QAnimationGroup_function_names[_id],
        qtscript_QAnimationGroup_function_signatures[_id]);
}

static QScriptValue qtscript_QAnimationGroup_toScriptValue(QScriptEngine *engine, QAnimationGroup* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAnimationGroup_fromScriptValue(const QScriptValue &value, QAnimationGroup* &out)
{
    out = qobject_cast<QAnimationGroup*>(value.toQObject());
}

QScriptValue qtscript_create_QAnimationGroup_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAnimationGroup*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAnimationGroup*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractAnimation*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAnimationGroup_prototype_call, qtscript_QAnimationGroup_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAnimationGroup_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAnimationGroup*>(engine, qtscript_QAnimationGroup_toScriptValue, 
        qtscript_QAnimationGroup_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAnimationGroup_static_call, proto, qtscript_QAnimationGroup_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
