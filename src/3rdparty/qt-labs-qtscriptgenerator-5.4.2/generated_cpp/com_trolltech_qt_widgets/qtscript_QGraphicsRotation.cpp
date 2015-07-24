#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicstransform.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmatrix4x4.h>
#include <qobject.h>
#include <qvector3d.h>

#include "qtscriptshell_QGraphicsRotation.h"

static const char * const qtscript_QGraphicsRotation_function_names[] = {
    "QGraphicsRotation"
    // static
    // prototype
    , "setAxis"
    , "toString"
};

static const char * const qtscript_QGraphicsRotation_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "Axis axis"
""
};

static const int qtscript_QGraphicsRotation_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsRotation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsRotation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsRotation*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsRotation*)
Q_DECLARE_METATYPE(Qt::Axis)
Q_DECLARE_METATYPE(QGraphicsTransform*)

//
// QGraphicsRotation
//

static QScriptValue qtscript_QGraphicsRotation_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsRotation* _q_self = qscriptvalue_cast<QGraphicsRotation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsRotation.%0(): this object is not a QGraphicsRotation")
            .arg(qtscript_QGraphicsRotation_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        Qt::Axis _q_arg0 = qscriptvalue_cast<Qt::Axis>(context->argument(0));
        _q_self->setAxis(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QGraphicsRotation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsRotation_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsRotation_function_names[_id+1],
        qtscript_QGraphicsRotation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsRotation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsRotation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsRotation* _q_cpp_result = new QtScriptShell_QGraphicsRotation();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsRotation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QGraphicsRotation* _q_cpp_result = new QtScriptShell_QGraphicsRotation(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsRotation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsRotation_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsRotation_function_names[_id],
        qtscript_QGraphicsRotation_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsRotation_toScriptValue(QScriptEngine *engine, QGraphicsRotation* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsRotation_fromScriptValue(const QScriptValue &value, QGraphicsRotation* &out)
{
    out = qobject_cast<QGraphicsRotation*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsRotation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsRotation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsRotation*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsTransform*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsRotation_prototype_call, qtscript_QGraphicsRotation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsRotation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsRotation*>(engine, qtscript_QGraphicsRotation_toScriptValue, 
        qtscript_QGraphicsRotation_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsRotation_static_call, proto, qtscript_QGraphicsRotation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
