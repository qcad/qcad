#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qwebpluginfactory.h>
#include <QVariant>
#include <QUrl>
#include <qwebpluginfactory.h>

#include "qtscriptshell_QWebPluginFactory.h"

static const char * const qtscript_QWebPluginFactory_function_names[] = {
    "QWebPluginFactory"
    // static
    // prototype
    , "create"
    , "extension"
    , "plugins"
    , "refreshPlugins"
    , "supportsExtension"
    , "toString"
};

static const char * const qtscript_QWebPluginFactory_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String mimeType, QUrl arg__2, List argumentNames, List argumentValues"
    , "Extension extension, QWebPluginFactory_ExtensionOption option, QWebPluginFactory_ExtensionReturn output"
    , ""
    , ""
    , "Extension extension"
""
};

static const int qtscript_QWebPluginFactory_function_lengths[] = {
    1
    // static
    // prototype
    , 4
    , 3
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QWebPluginFactory_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebPluginFactory::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebPluginFactory*)
Q_DECLARE_METATYPE(QtScriptShell_QWebPluginFactory*)
Q_DECLARE_METATYPE(QWebPluginFactory::Extension)
Q_DECLARE_METATYPE(const QWebPluginFactory::ExtensionOption*)
Q_DECLARE_METATYPE(QWebPluginFactory::ExtensionReturn*)
Q_DECLARE_METATYPE(QWebPluginFactory::Plugin)
Q_DECLARE_METATYPE(QList<QWebPluginFactory::Plugin >)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QWebPluginFactory::Extension
//

//static const QWebPluginFactory::Extension qtscript_QWebPluginFactory_Extension_values[] = {
//};

//static const char * const qtscript_QWebPluginFactory_Extension_keys[] = {
//};

static QString qtscript_QWebPluginFactory_Extension_toStringHelper(QWebPluginFactory::Extension value)
{
    //for (int i = 0; i < 0; ++i) {
    //    if (qtscript_QWebPluginFactory_Extension_values[i] == value)
    //        return QString::fromLatin1(qtscript_QWebPluginFactory_Extension_keys[i]);
    //}
    return QString();
}

static QScriptValue qtscript_QWebPluginFactory_Extension_toScriptValue(QScriptEngine *engine, const QWebPluginFactory::Extension &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebPluginFactory"));
    return clazz.property(qtscript_QWebPluginFactory_Extension_toStringHelper(value));
}

static void qtscript_QWebPluginFactory_Extension_fromScriptValue(const QScriptValue &value, QWebPluginFactory::Extension &out)
{
    out = qvariant_cast<QWebPluginFactory::Extension>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebPluginFactory_Extension(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    //for (int i = 0; i < 0; ++i) {
    //    if (qtscript_QWebPluginFactory_Extension_values[i] == arg)
    //        return qScriptValueFromValue(engine,  static_cast<QWebPluginFactory::Extension>(arg));
    //}
    return context->throwError(QString::fromLatin1("Extension(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebPluginFactory_Extension_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebPluginFactory::Extension value = qscriptvalue_cast<QWebPluginFactory::Extension>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebPluginFactory_Extension_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebPluginFactory::Extension value = qscriptvalue_cast<QWebPluginFactory::Extension>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebPluginFactory_Extension_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebPluginFactory_Extension_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebPluginFactory_Extension,
        qtscript_QWebPluginFactory_Extension_valueOf, qtscript_QWebPluginFactory_Extension_toString);
    qScriptRegisterMetaType<QWebPluginFactory::Extension>(engine, qtscript_QWebPluginFactory_Extension_toScriptValue,
        qtscript_QWebPluginFactory_Extension_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    //for (int i = 0; i < 0; ++i) {
    //    clazz.setProperty(QString::fromLatin1(qtscript_QWebPluginFactory_Extension_keys[i]),
    //        engine->newVariant(qVariantFromValue(qtscript_QWebPluginFactory_Extension_values[i])),
    //        QScriptValue::ReadOnly | QScriptValue::Undeletable);
    //}
    return ctor;
}

//
// QWebPluginFactory
//

static QScriptValue qtscript_QWebPluginFactory_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWebPluginFactory* _q_self = qscriptvalue_cast<QWebPluginFactory*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebPluginFactory.%0(): this object is not a QWebPluginFactory")
            .arg(qtscript_QWebPluginFactory_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
        QStringList _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QStringList _q_arg3;
        qScriptValueToSequence(context->argument(3), _q_arg3);
        QObject* _q_result = _q_self->create(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWebPluginFactory::Extension _q_arg0 = qscriptvalue_cast<QWebPluginFactory::Extension>(context->argument(0));
        bool _q_result = _q_self->extension(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWebPluginFactory::Extension _q_arg0 = qscriptvalue_cast<QWebPluginFactory::Extension>(context->argument(0));
        const QWebPluginFactory::ExtensionOption* _q_arg1 = qscriptvalue_cast<const QWebPluginFactory::ExtensionOption*>(context->argument(1));
        bool _q_result = _q_self->extension(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWebPluginFactory::Extension _q_arg0 = qscriptvalue_cast<QWebPluginFactory::Extension>(context->argument(0));
        const QWebPluginFactory::ExtensionOption* _q_arg1 = qscriptvalue_cast<const QWebPluginFactory::ExtensionOption*>(context->argument(1));
        QWebPluginFactory::ExtensionReturn* _q_arg2 = qscriptvalue_cast<QWebPluginFactory::ExtensionReturn*>(context->argument(2));
        bool _q_result = _q_self->extension(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QWebPluginFactory::Plugin > _q_result = _q_self->plugins();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->refreshPlugins();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWebPluginFactory::Extension _q_arg0 = qscriptvalue_cast<QWebPluginFactory::Extension>(context->argument(0));
        bool _q_result = _q_self->supportsExtension(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QWebPluginFactory");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPluginFactory_throw_ambiguity_error_helper(context,
        qtscript_QWebPluginFactory_function_names[_id+1],
        qtscript_QWebPluginFactory_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebPluginFactory_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebPluginFactory(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWebPluginFactory* _q_cpp_result = new QtScriptShell_QWebPluginFactory();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWebPluginFactory*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QWebPluginFactory* _q_cpp_result = new QtScriptShell_QWebPluginFactory(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWebPluginFactory*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPluginFactory_throw_ambiguity_error_helper(context,
        qtscript_QWebPluginFactory_function_names[_id],
        qtscript_QWebPluginFactory_function_signatures[_id]);
}

QScriptValue qtscript_create_QWebPluginFactory_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebPluginFactory*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebPluginFactory*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebPluginFactory_prototype_call, qtscript_QWebPluginFactory_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebPluginFactory_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWebPluginFactory*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebPluginFactory_static_call, proto, qtscript_QWebPluginFactory_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Extension"),
        qtscript_create_QWebPluginFactory_Extension_class(engine, ctor));
    return ctor;
}
