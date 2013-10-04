#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qglpixelbuffer.h>
#include <QImage>
#include <QVariant>
#include <qgl.h>
#include <qglpixelbuffer.h>
#include <qimage.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qsize.h>

#include "qtscriptshell_QGLPixelBuffer.h"

static const char * const qtscript_QGLPixelBuffer_function_names[] = {
    "QGLPixelBuffer"
    // static
    , "hasOpenGLPbuffers"
    // prototype
    , "doneCurrent"
    , "format"
    , "handle"
    , "isValid"
    , "makeCurrent"
    , "releaseFromDynamicTexture"
    , "size"
    , "toImage"
    , "toString"
};

static const char * const qtscript_QGLPixelBuffer_function_signatures[] = {
    "QSize size, QGLFormat format, QGLWidget shareWidget\nint width, int height, QGLFormat format, QGLWidget shareWidget"
    // static
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

static const int qtscript_QGLPixelBuffer_function_lengths[] = {
    4
    // static
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

static QScriptValue qtscript_QGLPixelBuffer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLPixelBuffer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLPixelBuffer*)
Q_DECLARE_METATYPE(QtScriptShell_QGLPixelBuffer*)
Q_DECLARE_METATYPE(QGLFormat)
Q_DECLARE_METATYPE(Qt::HANDLE)
Q_DECLARE_METATYPE(QGLWidget*)
Q_DECLARE_METATYPE(QPaintDevice*)

//
// QGLPixelBuffer
//

static QScriptValue qtscript_QGLPixelBuffer_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGLPixelBuffer* _q_self = qscriptvalue_cast<QGLPixelBuffer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLPixelBuffer.%0(): this object is not a QGLPixelBuffer")
            .arg(qtscript_QGLPixelBuffer_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->doneCurrent();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QGLFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        Qt::HANDLE _q_result = _q_self->handle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->makeCurrent();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->releaseFromDynamicTexture();
        return context->engine()->undefinedValue();
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
    QString result = QString::fromLatin1("QGLPixelBuffer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLPixelBuffer_throw_ambiguity_error_helper(context,
        qtscript_QGLPixelBuffer_function_names[_id+2],
        qtscript_QGLPixelBuffer_function_signatures[_id+2]);
}

static QScriptValue qtscript_QGLPixelBuffer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLPixelBuffer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QtScriptShell_QGLPixelBuffer* _q_cpp_result = new QtScriptShell_QGLPixelBuffer(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLPixelBuffer*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QGLFormat>() == context->argument(1).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QGLFormat _q_arg1 = qscriptvalue_cast<QGLFormat>(context->argument(1));
            QtScriptShell_QGLPixelBuffer* _q_cpp_result = new QtScriptShell_QGLPixelBuffer(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLPixelBuffer*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QGLPixelBuffer* _q_cpp_result = new QtScriptShell_QGLPixelBuffer(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLPixelBuffer*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QGLFormat>() == context->argument(1).toVariant().userType())
            && qscriptvalue_cast<QGLWidget*>(context->argument(2))) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QGLFormat _q_arg1 = qscriptvalue_cast<QGLFormat>(context->argument(1));
            QGLWidget* _q_arg2 = qscriptvalue_cast<QGLWidget*>(context->argument(2));
            QtScriptShell_QGLPixelBuffer* _q_cpp_result = new QtScriptShell_QGLPixelBuffer(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLPixelBuffer*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QGLFormat>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QGLFormat _q_arg2 = qscriptvalue_cast<QGLFormat>(context->argument(2));
            QtScriptShell_QGLPixelBuffer* _q_cpp_result = new QtScriptShell_QGLPixelBuffer(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLPixelBuffer*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QGLFormat _q_arg2 = qscriptvalue_cast<QGLFormat>(context->argument(2));
        QGLWidget* _q_arg3 = qscriptvalue_cast<QGLWidget*>(context->argument(3));
        QtScriptShell_QGLPixelBuffer* _q_cpp_result = new QtScriptShell_QGLPixelBuffer(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLPixelBuffer*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QGLPixelBuffer::hasOpenGLPbuffers();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLPixelBuffer_throw_ambiguity_error_helper(context,
        qtscript_QGLPixelBuffer_function_names[_id],
        qtscript_QGLPixelBuffer_function_signatures[_id]);
}

QScriptValue qtscript_create_QGLPixelBuffer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLPixelBuffer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLPixelBuffer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QPaintDevice*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLPixelBuffer_prototype_call, qtscript_QGLPixelBuffer_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLPixelBuffer_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGLPixelBuffer*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLPixelBuffer_static_call, proto, qtscript_QGLPixelBuffer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLPixelBuffer_static_call,
            qtscript_QGLPixelBuffer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGLPixelBuffer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
