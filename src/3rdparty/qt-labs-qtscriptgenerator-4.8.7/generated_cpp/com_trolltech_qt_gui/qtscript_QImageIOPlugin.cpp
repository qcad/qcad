#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qimageiohandler.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qimageiohandler.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

#include "qtscriptshell_QImageIOPlugin.h"

static const char * const qtscript_QImageIOPlugin_function_names[] = {
    "QImageIOPlugin"
    // static
    // prototype
    , "capabilities"
    , "create"
    , "keys"
    , "toString"
};

static const char * const qtscript_QImageIOPlugin_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QIODevice device, QByteArray format"
    , "QIODevice device, QByteArray format"
    , ""
""
};

static const int qtscript_QImageIOPlugin_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QImageIOPlugin_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QImageIOPlugin::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QImageIOPlugin*)
Q_DECLARE_METATYPE(QtScriptShell_QImageIOPlugin*)
Q_DECLARE_METATYPE(QImageIOPlugin::Capability)
Q_DECLARE_METATYPE(QFlags<QImageIOPlugin::Capability>)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QImageIOHandler*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QImageIOPlugin::Capability
//

static const QImageIOPlugin::Capability qtscript_QImageIOPlugin_Capability_values[] = {
    QImageIOPlugin::CanRead
    , QImageIOPlugin::CanWrite
    , QImageIOPlugin::CanReadIncremental
};

static const char * const qtscript_QImageIOPlugin_Capability_keys[] = {
    "CanRead"
    , "CanWrite"
    , "CanReadIncremental"
};

static QString qtscript_QImageIOPlugin_Capability_toStringHelper(QImageIOPlugin::Capability value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QImageIOPlugin_Capability_values[i] == value)
            return QString::fromLatin1(qtscript_QImageIOPlugin_Capability_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QImageIOPlugin_Capability_toScriptValue(QScriptEngine *engine, const QImageIOPlugin::Capability &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QImageIOPlugin"));
    return clazz.property(qtscript_QImageIOPlugin_Capability_toStringHelper(value));
}

static void qtscript_QImageIOPlugin_Capability_fromScriptValue(const QScriptValue &value, QImageIOPlugin::Capability &out)
{
    out = qvariant_cast<QImageIOPlugin::Capability>(value.toVariant());
}

static QScriptValue qtscript_construct_QImageIOPlugin_Capability(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QImageIOPlugin_Capability_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QImageIOPlugin::Capability>(arg));
    }
    return context->throwError(QString::fromLatin1("Capability(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QImageIOPlugin_Capability_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QImageIOPlugin::Capability value = qscriptvalue_cast<QImageIOPlugin::Capability>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QImageIOPlugin_Capability_toString(QScriptContext *context, QScriptEngine *engine)
{
    QImageIOPlugin::Capability value = qscriptvalue_cast<QImageIOPlugin::Capability>(context->thisObject());
    return QScriptValue(engine, qtscript_QImageIOPlugin_Capability_toStringHelper(value));
}

static QScriptValue qtscript_create_QImageIOPlugin_Capability_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QImageIOPlugin_Capability,
        qtscript_QImageIOPlugin_Capability_valueOf, qtscript_QImageIOPlugin_Capability_toString);
    qScriptRegisterMetaType<QImageIOPlugin::Capability>(engine, qtscript_QImageIOPlugin_Capability_toScriptValue,
        qtscript_QImageIOPlugin_Capability_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QImageIOPlugin_Capability_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QImageIOPlugin_Capability_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QImageIOPlugin::Capabilities
//

static QScriptValue qtscript_QImageIOPlugin_Capabilities_toScriptValue(QScriptEngine *engine, const QImageIOPlugin::Capabilities &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QImageIOPlugin_Capabilities_fromScriptValue(const QScriptValue &value, QImageIOPlugin::Capabilities &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QImageIOPlugin::Capabilities>())
        out = qvariant_cast<QImageIOPlugin::Capabilities>(var);
    else if (var.userType() == qMetaTypeId<QImageIOPlugin::Capability>())
        out = qvariant_cast<QImageIOPlugin::Capability>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QImageIOPlugin_Capabilities(QScriptContext *context, QScriptEngine *engine)
{
    QImageIOPlugin::Capabilities result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QImageIOPlugin::Capabilities>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QImageIOPlugin::Capability>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Capabilities(): argument %0 is not of type Capability").arg(i));
            }
            result |= qvariant_cast<QImageIOPlugin::Capability>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QImageIOPlugin_Capabilities_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QImageIOPlugin::Capabilities value = qscriptvalue_cast<QImageIOPlugin::Capabilities>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QImageIOPlugin_Capabilities_toString(QScriptContext *context, QScriptEngine *engine)
{
    QImageIOPlugin::Capabilities value = qscriptvalue_cast<QImageIOPlugin::Capabilities>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QImageIOPlugin_Capability_values[i]) == qtscript_QImageIOPlugin_Capability_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QImageIOPlugin_Capability_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QImageIOPlugin_Capabilities_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QImageIOPlugin::Capabilities>() == otherObj.value<QImageIOPlugin::Capabilities>())));
}

static QScriptValue qtscript_create_QImageIOPlugin_Capabilities_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QImageIOPlugin_Capabilities, qtscript_QImageIOPlugin_Capabilities_valueOf,
        qtscript_QImageIOPlugin_Capabilities_toString, qtscript_QImageIOPlugin_Capabilities_equals);
    qScriptRegisterMetaType<QImageIOPlugin::Capabilities>(engine, qtscript_QImageIOPlugin_Capabilities_toScriptValue,
        qtscript_QImageIOPlugin_Capabilities_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QImageIOPlugin
//

static QScriptValue qtscript_QImageIOPlugin_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QImageIOPlugin* _q_self = qscriptvalue_cast<QImageIOPlugin*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QImageIOPlugin.%0(): this object is not a QImageIOPlugin")
            .arg(qtscript_QImageIOPlugin_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QFlags<QImageIOPlugin::Capability> _q_result = _q_self->capabilities(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QImageIOHandler* _q_result = _q_self->create(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QImageIOHandler* _q_result = _q_self->create(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->keys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QImageIOPlugin");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageIOPlugin_throw_ambiguity_error_helper(context,
        qtscript_QImageIOPlugin_function_names[_id+1],
        qtscript_QImageIOPlugin_function_signatures[_id+1]);
}

static QScriptValue qtscript_QImageIOPlugin_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QImageIOPlugin(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QImageIOPlugin* _q_cpp_result = new QtScriptShell_QImageIOPlugin();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QImageIOPlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QImageIOPlugin* _q_cpp_result = new QtScriptShell_QImageIOPlugin(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QImageIOPlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QImageIOPlugin_throw_ambiguity_error_helper(context,
        qtscript_QImageIOPlugin_function_names[_id],
        qtscript_QImageIOPlugin_function_signatures[_id]);
}

static QScriptValue qtscript_QImageIOPlugin_toScriptValue(QScriptEngine *engine, QImageIOPlugin* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QImageIOPlugin_fromScriptValue(const QScriptValue &value, QImageIOPlugin* &out)
{
    out = qobject_cast<QImageIOPlugin*>(value.toQObject());
}

QScriptValue qtscript_create_QImageIOPlugin_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QImageIOPlugin*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QImageIOPlugin*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QImageIOPlugin_prototype_call, qtscript_QImageIOPlugin_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QImageIOPlugin_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QImageIOPlugin*>(engine, qtscript_QImageIOPlugin_toScriptValue, 
        qtscript_QImageIOPlugin_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QImageIOPlugin_static_call, proto, qtscript_QImageIOPlugin_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Capability"),
        qtscript_create_QImageIOPlugin_Capability_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Capabilities"),
        qtscript_create_QImageIOPlugin_Capabilities_class(engine));
    return ctor;
}
