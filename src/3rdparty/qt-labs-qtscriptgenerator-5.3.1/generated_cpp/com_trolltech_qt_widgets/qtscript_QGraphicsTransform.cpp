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

#include "qtscriptshell_QGraphicsTransform.h"

static const char * const qtscript_QGraphicsTransform_function_names[] = {
    "QGraphicsTransform"
    // static
    // prototype
    , "applyTo"
    , "toString"
};

static const char * const qtscript_QGraphicsTransform_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QMatrix4x4 matrix"
""
};

static const int qtscript_QGraphicsTransform_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsTransform_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsTransform::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsTransform*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsTransform*)
Q_DECLARE_METATYPE(QMatrix4x4*)

//
// QGraphicsTransform
//

static QScriptValue qtscript_QGraphicsTransform_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsTransform* _q_self = qscriptvalue_cast<QGraphicsTransform*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsTransform.%0(): this object is not a QGraphicsTransform")
            .arg(qtscript_QGraphicsTransform_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QMatrix4x4* _q_arg0 = qscriptvalue_cast<QMatrix4x4*>(context->argument(0));
        _q_self->applyTo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QGraphicsTransform");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsTransform_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsTransform_function_names[_id+1],
        qtscript_QGraphicsTransform_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsTransform_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsTransform(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsTransform* _q_cpp_result = new QtScriptShell_QGraphicsTransform();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTransform*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QGraphicsTransform* _q_cpp_result = new QtScriptShell_QGraphicsTransform(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTransform*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsTransform_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsTransform_function_names[_id],
        qtscript_QGraphicsTransform_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsTransform_toScriptValue(QScriptEngine *engine, QGraphicsTransform* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsTransform_fromScriptValue(const QScriptValue &value, QGraphicsTransform* &out)
{
    out = qobject_cast<QGraphicsTransform*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsTransform_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsTransform*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsTransform*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsTransform_prototype_call, qtscript_QGraphicsTransform_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsTransform_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsTransform*>(engine, qtscript_QGraphicsTransform_toScriptValue, 
        qtscript_QGraphicsTransform_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsTransform_static_call, proto, qtscript_QGraphicsTransform_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
