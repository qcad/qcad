#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qparallelanimationgroup.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qparallelanimationgroup.h>

#include "qtscriptshell_QParallelAnimationGroup.h"

static const char * const qtscript_QParallelAnimationGroup_function_names[] = {
    "QParallelAnimationGroup"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QParallelAnimationGroup_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QParallelAnimationGroup_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QParallelAnimationGroup_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QParallelAnimationGroup::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QParallelAnimationGroup*)
Q_DECLARE_METATYPE(QtScriptShell_QParallelAnimationGroup*)
Q_DECLARE_METATYPE(QAnimationGroup*)

//
// QParallelAnimationGroup
//

static QScriptValue qtscript_QParallelAnimationGroup_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QParallelAnimationGroup* _q_self = qscriptvalue_cast<QParallelAnimationGroup*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QParallelAnimationGroup.%0(): this object is not a QParallelAnimationGroup")
            .arg(qtscript_QParallelAnimationGroup_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QParallelAnimationGroup");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QParallelAnimationGroup_throw_ambiguity_error_helper(context,
        qtscript_QParallelAnimationGroup_function_names[_id+1],
        qtscript_QParallelAnimationGroup_function_signatures[_id+1]);
}

static QScriptValue qtscript_QParallelAnimationGroup_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QParallelAnimationGroup(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QParallelAnimationGroup* _q_cpp_result = new QtScriptShell_QParallelAnimationGroup();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QParallelAnimationGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QParallelAnimationGroup* _q_cpp_result = new QtScriptShell_QParallelAnimationGroup(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QParallelAnimationGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QParallelAnimationGroup_throw_ambiguity_error_helper(context,
        qtscript_QParallelAnimationGroup_function_names[_id],
        qtscript_QParallelAnimationGroup_function_signatures[_id]);
}

static QScriptValue qtscript_QParallelAnimationGroup_toScriptValue(QScriptEngine *engine, QParallelAnimationGroup* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QParallelAnimationGroup_fromScriptValue(const QScriptValue &value, QParallelAnimationGroup* &out)
{
    out = qobject_cast<QParallelAnimationGroup*>(value.toQObject());
}

QScriptValue qtscript_create_QParallelAnimationGroup_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QParallelAnimationGroup*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QParallelAnimationGroup*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAnimationGroup*>()));

    qScriptRegisterMetaType<QParallelAnimationGroup*>(engine, qtscript_QParallelAnimationGroup_toScriptValue, 
        qtscript_QParallelAnimationGroup_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QParallelAnimationGroup_static_call, proto, qtscript_QParallelAnimationGroup_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
