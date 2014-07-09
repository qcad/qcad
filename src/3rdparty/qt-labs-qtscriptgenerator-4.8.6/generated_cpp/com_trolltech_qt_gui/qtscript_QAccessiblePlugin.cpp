#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessibleplugin.h>
#include <QVariant>
#include <qaccessible.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

#include "qtscriptshell_QAccessiblePlugin.h"

static const char * const qtscript_QAccessiblePlugin_function_names[] = {
    "QAccessiblePlugin"
    // static
    // prototype
    , "create"
    , "keys"
    , "toString"
};

static const char * const qtscript_QAccessiblePlugin_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String key, QObject object"
    , ""
""
};

static const int qtscript_QAccessiblePlugin_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QAccessiblePlugin_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessiblePlugin::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessiblePlugin*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessiblePlugin*)
Q_DECLARE_METATYPE(QAccessibleInterface*)

//
// QAccessiblePlugin
//

static QScriptValue qtscript_QAccessiblePlugin_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAccessiblePlugin* _q_self = qscriptvalue_cast<QAccessiblePlugin*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessiblePlugin.%0(): this object is not a QAccessiblePlugin")
            .arg(qtscript_QAccessiblePlugin_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QAccessibleInterface* _q_result = _q_self->create(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->keys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QAccessiblePlugin");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessiblePlugin_throw_ambiguity_error_helper(context,
        qtscript_QAccessiblePlugin_function_names[_id+1],
        qtscript_QAccessiblePlugin_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessiblePlugin_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessiblePlugin(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAccessiblePlugin* _q_cpp_result = new QtScriptShell_QAccessiblePlugin();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAccessiblePlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAccessiblePlugin* _q_cpp_result = new QtScriptShell_QAccessiblePlugin(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAccessiblePlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessiblePlugin_throw_ambiguity_error_helper(context,
        qtscript_QAccessiblePlugin_function_names[_id],
        qtscript_QAccessiblePlugin_function_signatures[_id]);
}

static QScriptValue qtscript_QAccessiblePlugin_toScriptValue(QScriptEngine *engine, QAccessiblePlugin* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAccessiblePlugin_fromScriptValue(const QScriptValue &value, QAccessiblePlugin* &out)
{
    out = qobject_cast<QAccessiblePlugin*>(value.toQObject());
}

QScriptValue qtscript_create_QAccessiblePlugin_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessiblePlugin*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessiblePlugin*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessiblePlugin_prototype_call, qtscript_QAccessiblePlugin_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAccessiblePlugin_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAccessiblePlugin*>(engine, qtscript_QAccessiblePlugin_toScriptValue, 
        qtscript_QAccessiblePlugin_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessiblePlugin_static_call, proto, qtscript_QAccessiblePlugin_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
