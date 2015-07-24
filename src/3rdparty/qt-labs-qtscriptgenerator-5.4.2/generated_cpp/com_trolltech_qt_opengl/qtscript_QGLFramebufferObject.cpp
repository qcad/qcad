#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qglframebufferobject.h>
#include <QVariant>
#include <qglframebufferobject.h>
#include <qimage.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qsize.h>

#include "qtscriptshell_QGLFramebufferObject.h"

static const char * const qtscript_QGLFramebufferObject_function_names[] = {
    "QGLFramebufferObject"
    // static
    , "bindDefault"
    , "hasOpenGLFramebufferBlit"
    , "hasOpenGLFramebufferObjects"
    // prototype
    , "attachment"
    , "bind"
    , "format"
    , "isBound"
    , "isValid"
    , "release"
    , "size"
    , "toImage"
    , "toString"
};

static const char * const qtscript_QGLFramebufferObject_function_signatures[] = {
    "QSize size, QGLFramebufferObjectFormat format\nint width, int height, QGLFramebufferObjectFormat format"
    // static
    , ""
    , ""
    , ""
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QGLFramebufferObject_function_lengths[] = {
    3
    // static
    , 0
    , 0
    , 0
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGLFramebufferObject_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLFramebufferObject::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLFramebufferObject*)
Q_DECLARE_METATYPE(QtScriptShell_QGLFramebufferObject*)
Q_DECLARE_METATYPE(QGLFramebufferObject::Attachment)
Q_DECLARE_METATYPE(QGLFramebufferObjectFormat)
Q_DECLARE_METATYPE(QPaintDevice*)

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
// QGLFramebufferObject::Attachment
//

static const QGLFramebufferObject::Attachment qtscript_QGLFramebufferObject_Attachment_values[] = {
    QGLFramebufferObject::NoAttachment
    , QGLFramebufferObject::CombinedDepthStencil
    , QGLFramebufferObject::Depth
};

static const char * const qtscript_QGLFramebufferObject_Attachment_keys[] = {
    "NoAttachment"
    , "CombinedDepthStencil"
    , "Depth"
};

static QString qtscript_QGLFramebufferObject_Attachment_toStringHelper(QGLFramebufferObject::Attachment value)
{
    if ((value >= QGLFramebufferObject::NoAttachment) && (value <= QGLFramebufferObject::Depth))
        return qtscript_QGLFramebufferObject_Attachment_keys[static_cast<int>(value)-static_cast<int>(QGLFramebufferObject::NoAttachment)];
    return QString();
}

static QScriptValue qtscript_QGLFramebufferObject_Attachment_toScriptValue(QScriptEngine *engine, const QGLFramebufferObject::Attachment &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGLFramebufferObject"));
    return clazz.property(qtscript_QGLFramebufferObject_Attachment_toStringHelper(value));
}

static void qtscript_QGLFramebufferObject_Attachment_fromScriptValue(const QScriptValue &value, QGLFramebufferObject::Attachment &out)
{
    out = qvariant_cast<QGLFramebufferObject::Attachment>(value.toVariant());
}

static QScriptValue qtscript_construct_QGLFramebufferObject_Attachment(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGLFramebufferObject::NoAttachment) && (arg <= QGLFramebufferObject::Depth))
        return qScriptValueFromValue(engine,  static_cast<QGLFramebufferObject::Attachment>(arg));
    return context->throwError(QString::fromLatin1("Attachment(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGLFramebufferObject_Attachment_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGLFramebufferObject::Attachment value = qscriptvalue_cast<QGLFramebufferObject::Attachment>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGLFramebufferObject_Attachment_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGLFramebufferObject::Attachment value = qscriptvalue_cast<QGLFramebufferObject::Attachment>(context->thisObject());
    return QScriptValue(engine, qtscript_QGLFramebufferObject_Attachment_toStringHelper(value));
}

static QScriptValue qtscript_create_QGLFramebufferObject_Attachment_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGLFramebufferObject_Attachment,
        qtscript_QGLFramebufferObject_Attachment_valueOf, qtscript_QGLFramebufferObject_Attachment_toString);
    qScriptRegisterMetaType<QGLFramebufferObject::Attachment>(engine, qtscript_QGLFramebufferObject_Attachment_toScriptValue,
        qtscript_QGLFramebufferObject_Attachment_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGLFramebufferObject_Attachment_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGLFramebufferObject_Attachment_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGLFramebufferObject
//

static QScriptValue qtscript_QGLFramebufferObject_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGLFramebufferObject* _q_self = qscriptvalue_cast<QGLFramebufferObject*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLFramebufferObject.%0(): this object is not a QGLFramebufferObject")
            .arg(qtscript_QGLFramebufferObject_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QGLFramebufferObject::Attachment _q_result = _q_self->attachment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->bind();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QGLFramebufferObjectFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isBound();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->release();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->toImage();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QGLFramebufferObject");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLFramebufferObject_throw_ambiguity_error_helper(context,
        qtscript_QGLFramebufferObject_function_names[_id+4],
        qtscript_QGLFramebufferObject_function_signatures[_id+4]);
}

static QScriptValue qtscript_QGLFramebufferObject_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLFramebufferObject(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QGLFramebufferObjectFormat _q_arg1 = qscriptvalue_cast<QGLFramebufferObjectFormat>(context->argument(1));
        QtScriptShell_QGLFramebufferObject* _q_cpp_result = new QtScriptShell_QGLFramebufferObject(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLFramebufferObject*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QGLFramebufferObjectFormat _q_arg2 = qscriptvalue_cast<QGLFramebufferObjectFormat>(context->argument(2));
        QtScriptShell_QGLFramebufferObject* _q_cpp_result = new QtScriptShell_QGLFramebufferObject(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLFramebufferObject*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QGLFramebufferObject::bindDefault();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = QGLFramebufferObject::hasOpenGLFramebufferBlit();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = QGLFramebufferObject::hasOpenGLFramebufferObjects();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLFramebufferObject_throw_ambiguity_error_helper(context,
        qtscript_QGLFramebufferObject_function_names[_id],
        qtscript_QGLFramebufferObject_function_signatures[_id]);
}

QScriptValue qtscript_create_QGLFramebufferObject_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLFramebufferObject*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLFramebufferObject*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QPaintDevice*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLFramebufferObject_prototype_call, qtscript_QGLFramebufferObject_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLFramebufferObject_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGLFramebufferObject*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLFramebufferObject_static_call, proto, qtscript_QGLFramebufferObject_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLFramebufferObject_static_call,
            qtscript_QGLFramebufferObject_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGLFramebufferObject_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Attachment"),
        qtscript_create_QGLFramebufferObject_Attachment_class(engine, ctor));
    return ctor;
}
