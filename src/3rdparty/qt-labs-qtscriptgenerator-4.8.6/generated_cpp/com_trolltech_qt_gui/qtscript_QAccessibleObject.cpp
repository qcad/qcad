#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessibleobject.h>
#include <QVariant>
#include <qaccessible.h>
#include <qaccessibleobject.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>

#include "qtscriptshell_QAccessibleObject.h"

static const char * const qtscript_QAccessibleObject_function_names[] = {
    "QAccessibleObject"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QAccessibleObject_function_signatures[] = {
    "QObject object"
    // static
    // prototype
""
};

static const int qtscript_QAccessibleObject_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QAccessibleObject_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessibleObject::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessibleObject*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessibleObject*)
Q_DECLARE_METATYPE(QAccessibleInterface*)

//
// QAccessibleObject
//

static QScriptValue qtscript_QAccessibleObject_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAccessibleObject* _q_self = qscriptvalue_cast<QAccessibleObject*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessibleObject.%0(): this object is not a QAccessibleObject")
            .arg(qtscript_QAccessibleObject_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QAccessibleObject");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleObject_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleObject_function_names[_id+1],
        qtscript_QAccessibleObject_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessibleObject_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessibleObject(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAccessibleObject* _q_cpp_result = new QtScriptShell_QAccessibleObject(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleObject*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleObject_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleObject_function_names[_id],
        qtscript_QAccessibleObject_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessibleObject_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessibleObject*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessibleObject*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAccessibleInterface*>()));

    engine->setDefaultPrototype(qMetaTypeId<QAccessibleObject*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessibleObject_static_call, proto, qtscript_QAccessibleObject_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
