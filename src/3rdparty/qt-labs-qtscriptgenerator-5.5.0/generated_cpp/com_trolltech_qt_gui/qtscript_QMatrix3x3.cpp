#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgenericmatrix.h>
#include <QVariant>

#include "qtscriptshell_QMatrix3x3.h"

static const char * const qtscript_QMatrix3x3_function_names[] = {
    "QMatrix3x3"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QMatrix3x3_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QMatrix3x3_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QMatrix3x3_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMatrix3x3::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMatrix3x3*)
Q_DECLARE_METATYPE(QtScriptShell_QMatrix3x3)
Q_DECLARE_METATYPE(QtScriptShell_QMatrix3x3*)

//
// QMatrix3x3
//

static QScriptValue qtscript_QMatrix3x3_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QMatrix3x3* _q_self = qscriptvalue_cast<QMatrix3x3*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMatrix3x3.%0(): this object is not a QMatrix3x3")
            .arg(qtscript_QMatrix3x3_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QMatrix3x3");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMatrix3x3_throw_ambiguity_error_helper(context,
        qtscript_QMatrix3x3_function_names[_id+1],
        qtscript_QMatrix3x3_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMatrix3x3_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMatrix3x3(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMatrix3x3 _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QMatrix3x3)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMatrix3x3_throw_ambiguity_error_helper(context,
        qtscript_QMatrix3x3_function_names[_id],
        qtscript_QMatrix3x3_function_signatures[_id]);
}

QScriptValue qtscript_create_QMatrix3x3_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMatrix3x3*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMatrix3x3*)0));

    engine->setDefaultPrototype(qMetaTypeId<QMatrix3x3>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QMatrix3x3*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMatrix3x3_static_call, proto, qtscript_QMatrix3x3_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
