#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qglshaderprogram.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qgl.h>
#include <qglshaderprogram.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QGLShader.h"

static const char * const qtscript_QGLShader_function_names[] = {
    "QGLShader"
    // static
    , "hasOpenGLShaders"
    // prototype
    , "compileSourceCode"
    , "compileSourceFile"
    , "isCompiled"
    , "log"
    , "shaderType"
    , "sourceCode"
    , "toString"
};

static const char * const qtscript_QGLShader_function_signatures[] = {
    "ShaderType type, QObject parent\nShaderType type, QGLContext context, QObject parent"
    // static
    , "ShaderType type, QGLContext context"
    // prototype
    , "QByteArray source\nString source\nchar source"
    , "String fileName"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QGLShader_function_lengths[] = {
    3
    // static
    , 2
    // prototype
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGLShader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLShader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLShader*)
Q_DECLARE_METATYPE(QtScriptShell_QGLShader*)
Q_DECLARE_METATYPE(QGLShader::ShaderTypeBit)
Q_DECLARE_METATYPE(QFlags<QGLShader::ShaderTypeBit>)
Q_DECLARE_METATYPE(const char*)
Q_DECLARE_METATYPE(const QGLContext*)

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
// QGLShader::ShaderTypeBit
//

static const QGLShader::ShaderTypeBit qtscript_QGLShader_ShaderTypeBit_values[] = {
    QGLShader::Vertex
    , QGLShader::Fragment
    , QGLShader::Geometry
};

static const char * const qtscript_QGLShader_ShaderTypeBit_keys[] = {
    "Vertex"
    , "Fragment"
    , "Geometry"
};

static QString qtscript_QGLShader_ShaderTypeBit_toStringHelper(QGLShader::ShaderTypeBit value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QGLShader_ShaderTypeBit_values[i] == value)
            return QString::fromLatin1(qtscript_QGLShader_ShaderTypeBit_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QGLShader_ShaderTypeBit_toScriptValue(QScriptEngine *engine, const QGLShader::ShaderTypeBit &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGLShader"));
    return clazz.property(qtscript_QGLShader_ShaderTypeBit_toStringHelper(value));
}

static void qtscript_QGLShader_ShaderTypeBit_fromScriptValue(const QScriptValue &value, QGLShader::ShaderTypeBit &out)
{
    out = qvariant_cast<QGLShader::ShaderTypeBit>(value.toVariant());
}

static QScriptValue qtscript_construct_QGLShader_ShaderTypeBit(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QGLShader_ShaderTypeBit_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QGLShader::ShaderTypeBit>(arg));
    }
    return context->throwError(QString::fromLatin1("ShaderTypeBit(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGLShader_ShaderTypeBit_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGLShader::ShaderTypeBit value = qscriptvalue_cast<QGLShader::ShaderTypeBit>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGLShader_ShaderTypeBit_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGLShader::ShaderTypeBit value = qscriptvalue_cast<QGLShader::ShaderTypeBit>(context->thisObject());
    return QScriptValue(engine, qtscript_QGLShader_ShaderTypeBit_toStringHelper(value));
}

static QScriptValue qtscript_create_QGLShader_ShaderTypeBit_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGLShader_ShaderTypeBit,
        qtscript_QGLShader_ShaderTypeBit_valueOf, qtscript_QGLShader_ShaderTypeBit_toString);
    qScriptRegisterMetaType<QGLShader::ShaderTypeBit>(engine, qtscript_QGLShader_ShaderTypeBit_toScriptValue,
        qtscript_QGLShader_ShaderTypeBit_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGLShader_ShaderTypeBit_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGLShader_ShaderTypeBit_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGLShader::ShaderType
//

static QScriptValue qtscript_QGLShader_ShaderType_toScriptValue(QScriptEngine *engine, const QGLShader::ShaderType &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QGLShader_ShaderType_fromScriptValue(const QScriptValue &value, QGLShader::ShaderType &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QGLShader::ShaderType>())
        out = qvariant_cast<QGLShader::ShaderType>(var);
    else if (var.userType() == qMetaTypeId<QGLShader::ShaderTypeBit>())
        out = qvariant_cast<QGLShader::ShaderTypeBit>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QGLShader_ShaderType(QScriptContext *context, QScriptEngine *engine)
{
    QGLShader::ShaderType result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QGLShader::ShaderType>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QGLShader::ShaderTypeBit>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ShaderType(): argument %0 is not of type ShaderTypeBit").arg(i));
            }
            result |= qvariant_cast<QGLShader::ShaderTypeBit>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QGLShader_ShaderType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGLShader::ShaderType value = qscriptvalue_cast<QGLShader::ShaderType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGLShader_ShaderType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGLShader::ShaderType value = qscriptvalue_cast<QGLShader::ShaderType>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QGLShader_ShaderTypeBit_values[i]) == qtscript_QGLShader_ShaderTypeBit_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QGLShader_ShaderTypeBit_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QGLShader_ShaderType_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QGLShader::ShaderType>() == otherObj.value<QGLShader::ShaderType>())));
}

static QScriptValue qtscript_create_QGLShader_ShaderType_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QGLShader_ShaderType, qtscript_QGLShader_ShaderType_valueOf,
        qtscript_QGLShader_ShaderType_toString, qtscript_QGLShader_ShaderType_equals);
    qScriptRegisterMetaType<QGLShader::ShaderType>(engine, qtscript_QGLShader_ShaderType_toScriptValue,
        qtscript_QGLShader_ShaderType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QGLShader
//

static QScriptValue qtscript_QGLShader_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGLShader* _q_self = qscriptvalue_cast<QGLShader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLShader.%0(): this object is not a QGLShader")
            .arg(qtscript_QGLShader_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_result = _q_self->compileSourceCode(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->compileSourceCode(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            bool _q_result = _q_self->compileSourceCode(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->compileSourceFile(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCompiled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->log();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QFlags<QGLShader::ShaderTypeBit> _q_result = _q_self->shaderType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->sourceCode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QGLShader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLShader_throw_ambiguity_error_helper(context,
        qtscript_QGLShader_function_names[_id+2],
        qtscript_QGLShader_function_signatures[_id+2]);
}

static QScriptValue qtscript_QGLShader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLShader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
        QtScriptShell_QGLShader* _q_cpp_result = new QtScriptShell_QGLShader(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShader*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QFlags<QGLShader::ShaderTypeBit> >() == context->argument(0).toVariant().userType())
            && context->argument(1).isQObject()) {
            QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
            QObject* _q_arg1 = context->argument(1).toQObject();
            QtScriptShell_QGLShader* _q_cpp_result = new QtScriptShell_QGLShader(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShader*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QFlags<QGLShader::ShaderTypeBit> >() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<const QGLContext*>(context->argument(1))) {
            QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
            const QGLContext* _q_arg1 = qscriptvalue_cast<const QGLContext*>(context->argument(1));
            QtScriptShell_QGLShader* _q_cpp_result = new QtScriptShell_QGLShader(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShader*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
        const QGLContext* _q_arg1 = qscriptvalue_cast<const QGLContext*>(context->argument(1));
        QObject* _q_arg2 = context->argument(2).toQObject();
        QtScriptShell_QGLShader* _q_cpp_result = new QtScriptShell_QGLShader(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShader*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
        bool _q_result = QGLShader::hasOpenGLShaders(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
        const QGLContext* _q_arg1 = qscriptvalue_cast<const QGLContext*>(context->argument(1));
        bool _q_result = QGLShader::hasOpenGLShaders(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLShader_throw_ambiguity_error_helper(context,
        qtscript_QGLShader_function_names[_id],
        qtscript_QGLShader_function_signatures[_id]);
}

static QScriptValue qtscript_QGLShader_toScriptValue(QScriptEngine *engine, QGLShader* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGLShader_fromScriptValue(const QScriptValue &value, QGLShader* &out)
{
    out = qobject_cast<QGLShader*>(value.toQObject());
}

QScriptValue qtscript_create_QGLShader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLShader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLShader*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLShader_prototype_call, qtscript_QGLShader_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLShader_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGLShader*>(engine, qtscript_QGLShader_toScriptValue, 
        qtscript_QGLShader_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLShader_static_call, proto, qtscript_QGLShader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLShader_static_call,
            qtscript_QGLShader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGLShader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ShaderTypeBit"),
        qtscript_create_QGLShader_ShaderTypeBit_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ShaderType"),
        qtscript_create_QGLShader_ShaderType_class(engine));
    return ctor;
}
