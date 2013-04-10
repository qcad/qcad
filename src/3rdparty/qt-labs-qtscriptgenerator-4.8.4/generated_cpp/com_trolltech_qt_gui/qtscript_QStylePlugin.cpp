#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstyleplugin.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qstyle.h>

#include "qtscriptshell_QStylePlugin.h"

static const char * const qtscript_QStylePlugin_function_names[] = {
    "QStylePlugin"
    // static
    // prototype
    , "create"
    , "keys"
    , "toString"
};

static const char * const qtscript_QStylePlugin_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String key"
    , ""
""
};

static const int qtscript_QStylePlugin_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QStylePlugin_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStylePlugin::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStylePlugin*)
Q_DECLARE_METATYPE(QtScriptShell_QStylePlugin*)
Q_DECLARE_METATYPE(QStyle*)

//
// QStylePlugin
//

static QScriptValue qtscript_QStylePlugin_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStylePlugin* _q_self = qscriptvalue_cast<QStylePlugin*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStylePlugin.%0(): this object is not a QStylePlugin")
            .arg(qtscript_QStylePlugin_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStyle* _q_result = _q_self->create(_q_arg0);
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
    QString result = QString::fromLatin1("QStylePlugin");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStylePlugin_throw_ambiguity_error_helper(context,
        qtscript_QStylePlugin_function_names[_id+1],
        qtscript_QStylePlugin_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStylePlugin_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStylePlugin(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStylePlugin* _q_cpp_result = new QtScriptShell_QStylePlugin();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStylePlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QStylePlugin* _q_cpp_result = new QtScriptShell_QStylePlugin(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStylePlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStylePlugin_throw_ambiguity_error_helper(context,
        qtscript_QStylePlugin_function_names[_id],
        qtscript_QStylePlugin_function_signatures[_id]);
}

static QScriptValue qtscript_QStylePlugin_toScriptValue(QScriptEngine *engine, QStylePlugin* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStylePlugin_fromScriptValue(const QScriptValue &value, QStylePlugin* &out)
{
    out = qobject_cast<QStylePlugin*>(value.toQObject());
}

QScriptValue qtscript_create_QStylePlugin_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStylePlugin*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStylePlugin*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStylePlugin_prototype_call, qtscript_QStylePlugin_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStylePlugin_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStylePlugin*>(engine, qtscript_QStylePlugin_toScriptValue, 
        qtscript_QStylePlugin_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStylePlugin_static_call, proto, qtscript_QStylePlugin_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
