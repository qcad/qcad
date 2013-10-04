#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qinputcontextplugin.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qinputcontext.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

#include "qtscriptshell_QInputContextPlugin.h"

static const char * const qtscript_QInputContextPlugin_function_names[] = {
    "QInputContextPlugin"
    // static
    // prototype
    , "create"
    , "description"
    , "displayName"
    , "keys"
    , "languages"
    , "toString"
};

static const char * const qtscript_QInputContextPlugin_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String key"
    , "String key"
    , "String key"
    , ""
    , "String key"
""
};

static const int qtscript_QInputContextPlugin_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QInputContextPlugin_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QInputContextPlugin::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QInputContextPlugin*)
Q_DECLARE_METATYPE(QtScriptShell_QInputContextPlugin*)
Q_DECLARE_METATYPE(QInputContext*)

//
// QInputContextPlugin
//

static QScriptValue qtscript_QInputContextPlugin_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QInputContextPlugin* _q_self = qscriptvalue_cast<QInputContextPlugin*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QInputContextPlugin.%0(): this object is not a QInputContextPlugin")
            .arg(qtscript_QInputContextPlugin_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QInputContext* _q_result = _q_self->create(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->description(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->displayName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->keys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = _q_self->languages(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QInputContextPlugin");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputContextPlugin_throw_ambiguity_error_helper(context,
        qtscript_QInputContextPlugin_function_names[_id+1],
        qtscript_QInputContextPlugin_function_signatures[_id+1]);
}

static QScriptValue qtscript_QInputContextPlugin_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QInputContextPlugin(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QInputContextPlugin* _q_cpp_result = new QtScriptShell_QInputContextPlugin();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QInputContextPlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QInputContextPlugin* _q_cpp_result = new QtScriptShell_QInputContextPlugin(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QInputContextPlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputContextPlugin_throw_ambiguity_error_helper(context,
        qtscript_QInputContextPlugin_function_names[_id],
        qtscript_QInputContextPlugin_function_signatures[_id]);
}

static QScriptValue qtscript_QInputContextPlugin_toScriptValue(QScriptEngine *engine, QInputContextPlugin* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QInputContextPlugin_fromScriptValue(const QScriptValue &value, QInputContextPlugin* &out)
{
    out = qobject_cast<QInputContextPlugin*>(value.toQObject());
}

QScriptValue qtscript_create_QInputContextPlugin_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QInputContextPlugin*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QInputContextPlugin*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QInputContextPlugin_prototype_call, qtscript_QInputContextPlugin_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QInputContextPlugin_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QInputContextPlugin*>(engine, qtscript_QInputContextPlugin_toScriptValue, 
        qtscript_QInputContextPlugin_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QInputContextPlugin_static_call, proto, qtscript_QInputContextPlugin_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
