#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmovie.h>
#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QRect>
#include <QSize>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qimage.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qmovie.h>
#include <qobject.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>

#include "qtscriptshell_QMovie.h"

static const char * const qtscript_QMovie_function_names[] = {
    "QMovie"
    // static
    , "supportedFormats"
    // prototype
    , "backgroundColor"
    , "currentFrameNumber"
    , "currentImage"
    , "currentPixmap"
    , "device"
    , "fileName"
    , "format"
    , "frameCount"
    , "frameRect"
    , "isValid"
    , "jumpToFrame"
    , "loopCount"
    , "nextFrameDelay"
    , "scaledSize"
    , "setBackgroundColor"
    , "setDevice"
    , "setFileName"
    , "setFormat"
    , "setScaledSize"
    , "state"
    , "toString"
};

static const char * const qtscript_QMovie_function_signatures[] = {
    "QIODevice device, QByteArray format, QObject parent\nQObject parent\nString fileName, QByteArray format, QObject parent"
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
    , ""
    , ""
    , "int frameNumber"
    , ""
    , ""
    , ""
    , "QColor color"
    , "QIODevice device"
    , "String fileName"
    , "QByteArray format"
    , "QSize size"
    , ""
""
};

static const int qtscript_QMovie_function_lengths[] = {
    3
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
    , 0
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QMovie_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMovie::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QMovie_metaObject()
{
    return &QMovie::staticMetaObject;
}

Q_DECLARE_METATYPE(QMovie*)
Q_DECLARE_METATYPE(QtScriptShell_QMovie*)
Q_DECLARE_METATYPE(QMovie::MovieState)
Q_DECLARE_METATYPE(QMovie::CacheMode)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QList<QByteArray >)

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
// QMovie::MovieState
//

static const QMovie::MovieState qtscript_QMovie_MovieState_values[] = {
    QMovie::NotRunning
    , QMovie::Paused
    , QMovie::Running
};

static const char * const qtscript_QMovie_MovieState_keys[] = {
    "NotRunning"
    , "Paused"
    , "Running"
};

static QString qtscript_QMovie_MovieState_toStringHelper(QMovie::MovieState value)
{
    const QMetaObject *meta = qtscript_QMovie_metaObject();
    int idx = meta->indexOfEnumerator("MovieState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QMovie_MovieState_toScriptValue(QScriptEngine *engine, const QMovie::MovieState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMovie"));
    return clazz.property(qtscript_QMovie_MovieState_toStringHelper(value));
}

static void qtscript_QMovie_MovieState_fromScriptValue(const QScriptValue &value, QMovie::MovieState &out)
{
    out = qvariant_cast<QMovie::MovieState>(value.toVariant());
}

static QScriptValue qtscript_construct_QMovie_MovieState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QMovie_metaObject();
    int idx = meta->indexOfEnumerator("MovieState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QMovie::MovieState>(arg));
    return context->throwError(QString::fromLatin1("MovieState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMovie_MovieState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMovie::MovieState value = qscriptvalue_cast<QMovie::MovieState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMovie_MovieState_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMovie::MovieState value = qscriptvalue_cast<QMovie::MovieState>(context->thisObject());
    return QScriptValue(engine, qtscript_QMovie_MovieState_toStringHelper(value));
}

static QScriptValue qtscript_create_QMovie_MovieState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMovie_MovieState,
        qtscript_QMovie_MovieState_valueOf, qtscript_QMovie_MovieState_toString);
    qScriptRegisterMetaType<QMovie::MovieState>(engine, qtscript_QMovie_MovieState_toScriptValue,
        qtscript_QMovie_MovieState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMovie_MovieState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMovie_MovieState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMovie::CacheMode
//

static const QMovie::CacheMode qtscript_QMovie_CacheMode_values[] = {
    QMovie::CacheNone
    , QMovie::CacheAll
};

static const char * const qtscript_QMovie_CacheMode_keys[] = {
    "CacheNone"
    , "CacheAll"
};

static QString qtscript_QMovie_CacheMode_toStringHelper(QMovie::CacheMode value)
{
    const QMetaObject *meta = qtscript_QMovie_metaObject();
    int idx = meta->indexOfEnumerator("CacheMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QMovie_CacheMode_toScriptValue(QScriptEngine *engine, const QMovie::CacheMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMovie"));
    return clazz.property(qtscript_QMovie_CacheMode_toStringHelper(value));
}

static void qtscript_QMovie_CacheMode_fromScriptValue(const QScriptValue &value, QMovie::CacheMode &out)
{
    out = qvariant_cast<QMovie::CacheMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QMovie_CacheMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QMovie_metaObject();
    int idx = meta->indexOfEnumerator("CacheMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QMovie::CacheMode>(arg));
    return context->throwError(QString::fromLatin1("CacheMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMovie_CacheMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMovie::CacheMode value = qscriptvalue_cast<QMovie::CacheMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMovie_CacheMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMovie::CacheMode value = qscriptvalue_cast<QMovie::CacheMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QMovie_CacheMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QMovie_CacheMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMovie_CacheMode,
        qtscript_QMovie_CacheMode_valueOf, qtscript_QMovie_CacheMode_toString);
    qScriptRegisterMetaType<QMovie::CacheMode>(engine, qtscript_QMovie_CacheMode_toScriptValue,
        qtscript_QMovie_CacheMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMovie_CacheMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMovie_CacheMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMovie
//

static QScriptValue qtscript_QMovie_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMovie* _q_self = qscriptvalue_cast<QMovie*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMovie.%0(): this object is not a QMovie")
            .arg(qtscript_QMovie_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->backgroundColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentFrameNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->currentImage();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->currentPixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->frameCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->frameRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->jumpToFrame(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loopCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->nextFrameDelay();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->scaledSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->setBackgroundColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        _q_self->setScaledSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QMovie::MovieState _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20: {
    QString result = QString::fromLatin1("QMovie");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMovie_throw_ambiguity_error_helper(context,
        qtscript_QMovie_function_names[_id+2],
        qtscript_QMovie_function_signatures[_id+2]);
}

static QScriptValue qtscript_QMovie_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMovie(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())
            && context->argument(2).isQObject()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QObject* _q_arg2 = context->argument(2).toQObject();
            QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())
            && context->argument(2).isQObject()) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QObject* _q_arg2 = context->argument(2).toQObject();
            QtScriptShell_QMovie* _q_cpp_result = new QtScriptShell_QMovie(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMovie*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = QMovie::supportedFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMovie_throw_ambiguity_error_helper(context,
        qtscript_QMovie_function_names[_id],
        qtscript_QMovie_function_signatures[_id]);
}

static QScriptValue qtscript_QMovie_toScriptValue(QScriptEngine *engine, QMovie* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMovie_fromScriptValue(const QScriptValue &value, QMovie* &out)
{
    out = qobject_cast<QMovie*>(value.toQObject());
}

QScriptValue qtscript_create_QMovie_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMovie*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMovie*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMovie_prototype_call, qtscript_QMovie_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMovie_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMovie*>(engine, qtscript_QMovie_toScriptValue, 
        qtscript_QMovie_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMovie_static_call, proto, qtscript_QMovie_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMovie_static_call,
            qtscript_QMovie_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QMovie_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("MovieState"),
        qtscript_create_QMovie_MovieState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CacheMode"),
        qtscript_create_QMovie_CacheMode_class(engine, ctor));
    return ctor;
}
