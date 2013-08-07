#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstylefactory.h>
#include <QVariant>
#include <qstringlist.h>
#include <qstyle.h>

#include "qtscriptshell_QStyleFactory.h"

static const char * const qtscript_QStyleFactory_function_names[] = {
    "QStyleFactory"
    // static
    , "create"
    , "keys"
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleFactory_function_signatures[] = {
    ""
    // static
    , "String arg__1"
    , ""
    // prototype
""
};

static const int qtscript_QStyleFactory_function_lengths[] = {
    0
    // static
    , 1
    , 0
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleFactory_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleFactory::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleFactory*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleFactory*)
Q_DECLARE_METATYPE(QStyle*)

//
// QStyleFactory
//

static QScriptValue qtscript_QStyleFactory_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleFactory* _q_self = qscriptvalue_cast<QStyleFactory*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleFactory.%0(): this object is not a QStyleFactory")
            .arg(qtscript_QStyleFactory_function_names[_id+3]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleFactory");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleFactory_throw_ambiguity_error_helper(context,
        qtscript_QStyleFactory_function_names[_id+3],
        qtscript_QStyleFactory_function_signatures[_id+3]);
}

static QScriptValue qtscript_QStyleFactory_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleFactory(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleFactory* _q_cpp_result = new QtScriptShell_QStyleFactory();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleFactory*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStyle* _q_result = QStyleFactory::create(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QStyleFactory::keys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleFactory_throw_ambiguity_error_helper(context,
        qtscript_QStyleFactory_function_names[_id],
        qtscript_QStyleFactory_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleFactory_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleFactory*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleFactory*)0));

    engine->setDefaultPrototype(qMetaTypeId<QStyleFactory*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleFactory_static_call, proto, qtscript_QStyleFactory_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStyleFactory_static_call,
            qtscript_QStyleFactory_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QStyleFactory_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
