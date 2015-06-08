#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qiconengineplugin.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

#include "qtscriptshell_QIconEnginePluginV2.h"

static const char * const qtscript_QIconEnginePluginV2_function_names[] = {
    "QIconEnginePluginV2"
    // static
    // prototype
    , "create"
    , "keys"
    , "toString"
};

static const char * const qtscript_QIconEnginePluginV2_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String filename"
    , ""
""
};

static const int qtscript_QIconEnginePluginV2_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QIconEnginePluginV2_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QIconEnginePluginV2::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QIconEnginePluginV2*)
Q_DECLARE_METATYPE(QtScriptShell_QIconEnginePluginV2*)
Q_DECLARE_METATYPE(QIconEngineV2*)

//
// QIconEnginePluginV2
//

static QScriptValue qtscript_QIconEnginePluginV2_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QIconEnginePluginV2* _q_self = qscriptvalue_cast<QIconEnginePluginV2*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QIconEnginePluginV2.%0(): this object is not a QIconEnginePluginV2")
            .arg(qtscript_QIconEnginePluginV2_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QIconEngineV2* _q_result = _q_self->create();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QIconEngineV2* _q_result = _q_self->create(_q_arg0);
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
    QString result = QString::fromLatin1("QIconEnginePluginV2");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIconEnginePluginV2_throw_ambiguity_error_helper(context,
        qtscript_QIconEnginePluginV2_function_names[_id+1],
        qtscript_QIconEnginePluginV2_function_signatures[_id+1]);
}

static QScriptValue qtscript_QIconEnginePluginV2_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QIconEnginePluginV2(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QIconEnginePluginV2* _q_cpp_result = new QtScriptShell_QIconEnginePluginV2();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIconEnginePluginV2*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QIconEnginePluginV2* _q_cpp_result = new QtScriptShell_QIconEnginePluginV2(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIconEnginePluginV2*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIconEnginePluginV2_throw_ambiguity_error_helper(context,
        qtscript_QIconEnginePluginV2_function_names[_id],
        qtscript_QIconEnginePluginV2_function_signatures[_id]);
}

static QScriptValue qtscript_QIconEnginePluginV2_toScriptValue(QScriptEngine *engine, QIconEnginePluginV2* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QIconEnginePluginV2_fromScriptValue(const QScriptValue &value, QIconEnginePluginV2* &out)
{
    out = qobject_cast<QIconEnginePluginV2*>(value.toQObject());
}

QScriptValue qtscript_create_QIconEnginePluginV2_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QIconEnginePluginV2*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QIconEnginePluginV2*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QIconEnginePluginV2_prototype_call, qtscript_QIconEnginePluginV2_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QIconEnginePluginV2_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QIconEnginePluginV2*>(engine, qtscript_QIconEnginePluginV2_toScriptValue, 
        qtscript_QIconEnginePluginV2_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QIconEnginePluginV2_static_call, proto, qtscript_QIconEnginePluginV2_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
