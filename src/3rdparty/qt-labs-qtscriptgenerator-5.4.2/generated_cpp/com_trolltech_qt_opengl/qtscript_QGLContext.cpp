#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgl.h>
#include <QVariant>
#include <qcolor.h>
#include <qgl.h>
#include <qpaintdevice.h>

#include "qtscriptshell_QGLContext.h"

static const char * const qtscript_QGLContext_function_names[] = {
    "QGLContext"
    // static
    , "areSharing"
    , "currentContext"
    , "setTextureCacheLimit"
    , "textureCacheLimit"
    // prototype
    , "create"
    , "device"
    , "doneCurrent"
    , "format"
    , "isSharing"
    , "isValid"
    , "makeCurrent"
    , "moveToThread"
    , "overlayTransparentColor"
    , "requestedFormat"
    , "reset"
    , "setFormat"
    , "swapBuffers"
    , "toString"
};

static const char * const qtscript_QGLContext_function_signatures[] = {
    "QGLFormat format\nQGLFormat format, QPaintDevice device"
    // static
    , "QGLContext context1, QGLContext context2"
    , ""
    , "int size"
    , ""
    // prototype
    , "QGLContext shareContext"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "Thread thread"
    , ""
    , ""
    , ""
    , "QGLFormat format"
    , ""
""
};

static const int qtscript_QGLContext_function_lengths[] = {
    2
    // static
    , 2
    , 0
    , 1
    , 0
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGLContext_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLContext::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLContext*)
Q_DECLARE_METATYPE(QtScriptShell_QGLContext*)
Q_DECLARE_METATYPE(QGLContext::BindOption)
Q_DECLARE_METATYPE(QFlags<QGLContext::BindOption>)
Q_DECLARE_METATYPE(const QGLContext*)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QGLFormat)
Q_DECLARE_METATYPE(QThread*)

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
// QGLContext::BindOption
//

static const QGLContext::BindOption qtscript_QGLContext_BindOption_values[] = {
    QGLContext::NoBindOption
    , QGLContext::InvertedYBindOption
    , QGLContext::MipmapBindOption
    , QGLContext::PremultipliedAlphaBindOption
    , QGLContext::LinearFilteringBindOption
    , QGLContext::DefaultBindOption
    , QGLContext::MemoryManagedBindOption
    , QGLContext::InternalBindOption
    , QGLContext::CanFlipNativePixmapBindOption
    , QGLContext::TemporarilyCachedBindOption
};

static const char * const qtscript_QGLContext_BindOption_keys[] = {
    "NoBindOption"
    , "InvertedYBindOption"
    , "MipmapBindOption"
    , "PremultipliedAlphaBindOption"
    , "LinearFilteringBindOption"
    , "DefaultBindOption"
    , "MemoryManagedBindOption"
    , "InternalBindOption"
    , "CanFlipNativePixmapBindOption"
    , "TemporarilyCachedBindOption"
};

static QString qtscript_QGLContext_BindOption_toStringHelper(QGLContext::BindOption value)
{
    for (int i = 0; i < 10; ++i) {
        if (qtscript_QGLContext_BindOption_values[i] == value)
            return QString::fromLatin1(qtscript_QGLContext_BindOption_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QGLContext_BindOption_toScriptValue(QScriptEngine *engine, const QGLContext::BindOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGLContext"));
    return clazz.property(qtscript_QGLContext_BindOption_toStringHelper(value));
}

static void qtscript_QGLContext_BindOption_fromScriptValue(const QScriptValue &value, QGLContext::BindOption &out)
{
    out = qvariant_cast<QGLContext::BindOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QGLContext_BindOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 10; ++i) {
        if (qtscript_QGLContext_BindOption_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QGLContext::BindOption>(arg));
    }
    return context->throwError(QString::fromLatin1("BindOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGLContext_BindOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGLContext::BindOption value = qscriptvalue_cast<QGLContext::BindOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGLContext_BindOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGLContext::BindOption value = qscriptvalue_cast<QGLContext::BindOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QGLContext_BindOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QGLContext_BindOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGLContext_BindOption,
        qtscript_QGLContext_BindOption_valueOf, qtscript_QGLContext_BindOption_toString);
    qScriptRegisterMetaType<QGLContext::BindOption>(engine, qtscript_QGLContext_BindOption_toScriptValue,
        qtscript_QGLContext_BindOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 10; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGLContext_BindOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGLContext_BindOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGLContext::BindOptions
//

static QScriptValue qtscript_QGLContext_BindOptions_toScriptValue(QScriptEngine *engine, const QGLContext::BindOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QGLContext_BindOptions_fromScriptValue(const QScriptValue &value, QGLContext::BindOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QGLContext::BindOptions>())
        out = qvariant_cast<QGLContext::BindOptions>(var);
    else if (var.userType() == qMetaTypeId<QGLContext::BindOption>())
        out = qvariant_cast<QGLContext::BindOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QGLContext_BindOptions(QScriptContext *context, QScriptEngine *engine)
{
    QGLContext::BindOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QGLContext::BindOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QGLContext::BindOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("BindOptions(): argument %0 is not of type BindOption").arg(i));
            }
            result |= qvariant_cast<QGLContext::BindOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QGLContext_BindOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGLContext::BindOptions value = qscriptvalue_cast<QGLContext::BindOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGLContext_BindOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGLContext::BindOptions value = qscriptvalue_cast<QGLContext::BindOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 10; ++i) {
        if ((value & qtscript_QGLContext_BindOption_values[i]) == qtscript_QGLContext_BindOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QGLContext_BindOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QGLContext_BindOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QGLContext::BindOptions>() == otherObj.value<QGLContext::BindOptions>())));
}

static QScriptValue qtscript_create_QGLContext_BindOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QGLContext_BindOptions, qtscript_QGLContext_BindOptions_valueOf,
        qtscript_QGLContext_BindOptions_toString, qtscript_QGLContext_BindOptions_equals);
    qScriptRegisterMetaType<QGLContext::BindOptions>(engine, qtscript_QGLContext_BindOptions_toScriptValue,
        qtscript_QGLContext_BindOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QGLContext
//

static QScriptValue qtscript_QGLContext_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGLContext* _q_self = qscriptvalue_cast<QGLContext*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLContext.%0(): this object is not a QGLContext")
            .arg(qtscript_QGLContext_function_names[_id+5]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->create();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        const QGLContext* _q_arg0 = qscriptvalue_cast<const QGLContext*>(context->argument(0));
        bool _q_result = _q_self->create(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPaintDevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->doneCurrent();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QGLFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSharing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->makeCurrent();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QThread* _q_arg0 = qscriptvalue_cast<QThread*>(context->argument(0));
        _q_self->moveToThread(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->overlayTransparentColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QGLFormat _q_result = _q_self->requestedFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QGLFormat _q_arg0 = qscriptvalue_cast<QGLFormat>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        _q_self->swapBuffers();
        return context->engine()->undefinedValue();
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QGLContext");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLContext_throw_ambiguity_error_helper(context,
        qtscript_QGLContext_function_names[_id+5],
        qtscript_QGLContext_function_signatures[_id+5]);
}

static QScriptValue qtscript_QGLContext_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLContext(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QGLFormat _q_arg0 = qscriptvalue_cast<QGLFormat>(context->argument(0));
        QtScriptShell_QGLContext* _q_cpp_result = new QtScriptShell_QGLContext(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLContext*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QGLFormat _q_arg0 = qscriptvalue_cast<QGLFormat>(context->argument(0));
        QPaintDevice* _q_arg1 = qscriptvalue_cast<QPaintDevice*>(context->argument(1));
        QtScriptShell_QGLContext* _q_cpp_result = new QtScriptShell_QGLContext(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLContext*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        const QGLContext* _q_arg0 = qscriptvalue_cast<const QGLContext*>(context->argument(0));
        const QGLContext* _q_arg1 = qscriptvalue_cast<const QGLContext*>(context->argument(1));
        bool _q_result = QGLContext::areSharing(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        const QGLContext* _q_result = const_cast<const QGLContext*>(QGLContext::currentContext());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QGLContext::setTextureCacheLimit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = QGLContext::textureCacheLimit();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLContext_throw_ambiguity_error_helper(context,
        qtscript_QGLContext_function_names[_id],
        qtscript_QGLContext_function_signatures[_id]);
}

QScriptValue qtscript_create_QGLContext_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLContext*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLContext*)0));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLContext_prototype_call, qtscript_QGLContext_function_lengths[i+5]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLContext_function_names[i+5]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGLContext*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLContext_static_call, proto, qtscript_QGLContext_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLContext_static_call,
            qtscript_QGLContext_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGLContext_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("BindOption"),
        qtscript_create_QGLContext_BindOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BindOptions"),
        qtscript_create_QGLContext_BindOptions_class(engine));
    return ctor;
}
