#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qinputcontextfactory.h>
#include <QVariant>
#include <qinputcontext.h>
#include <qobject.h>
#include <qstringlist.h>

#include "qtscriptshell_QInputContextFactory.h"

static const char * const qtscript_QInputContextFactory_function_names[] = {
    "QInputContextFactory"
    // static
    , "create"
    , "description"
    , "displayName"
    , "keys"
    , "languages"
    // prototype
    , "toString"
};

static const char * const qtscript_QInputContextFactory_function_signatures[] = {
    ""
    // static
    , "String key, QObject parent"
    , "String key"
    , "String key"
    , ""
    , "String key"
    // prototype
""
};

static const int qtscript_QInputContextFactory_function_lengths[] = {
    0
    // static
    , 2
    , 1
    , 1
    , 0
    , 1
    // prototype
    , 0
};

static QScriptValue qtscript_QInputContextFactory_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QInputContextFactory::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QInputContextFactory*)
Q_DECLARE_METATYPE(QtScriptShell_QInputContextFactory*)
Q_DECLARE_METATYPE(QInputContext*)

//
// QInputContextFactory
//

static QScriptValue qtscript_QInputContextFactory_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QInputContextFactory* _q_self = qscriptvalue_cast<QInputContextFactory*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QInputContextFactory.%0(): this object is not a QInputContextFactory")
            .arg(qtscript_QInputContextFactory_function_names[_id+6]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QInputContextFactory");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputContextFactory_throw_ambiguity_error_helper(context,
        qtscript_QInputContextFactory_function_names[_id+6],
        qtscript_QInputContextFactory_function_signatures[_id+6]);
}

static QScriptValue qtscript_QInputContextFactory_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QInputContextFactory(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QInputContextFactory* _q_cpp_result = new QtScriptShell_QInputContextFactory();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QInputContextFactory*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QInputContext* _q_result = QInputContextFactory::create(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QInputContextFactory::description(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QInputContextFactory::displayName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QInputContextFactory::keys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = QInputContextFactory::languages(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputContextFactory_throw_ambiguity_error_helper(context,
        qtscript_QInputContextFactory_function_names[_id],
        qtscript_QInputContextFactory_function_signatures[_id]);
}

QScriptValue qtscript_create_QInputContextFactory_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QInputContextFactory*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QInputContextFactory*)0));

    engine->setDefaultPrototype(qMetaTypeId<QInputContextFactory*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QInputContextFactory_static_call, proto, qtscript_QInputContextFactory_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QInputContextFactory_static_call,
            qtscript_QInputContextFactory_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QInputContextFactory_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
