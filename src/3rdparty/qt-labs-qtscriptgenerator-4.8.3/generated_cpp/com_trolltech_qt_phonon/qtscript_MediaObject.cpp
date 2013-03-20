#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <mediaobject.h>
#include <QVariant>
#include <mediasource.h>
#include <path.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qurl.h>

#include "qtscriptshell_MediaObject.h"

static const char * const qtscript_MediaObject_function_names[] = {
    "MediaObject"
    // static
    // prototype
    , "clearQueue"
    , "currentSource"
    , "currentTime"
    , "enqueue"
    , "enqueueUrls"
    , "errorString"
    , "errorType"
    , "hasVideo"
    , "isSeekable"
    , "metaData"
    , "queue"
    , "remainingTime"
    , "setCurrentSource"
    , "setQueue"
    , "setQueueToUrls"
    , "state"
    , "totalTime"
    , "toString"
};

static const char * const qtscript_MediaObject_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "MediaSource source\nList sources"
    , "List urls"
    , ""
    , ""
    , ""
    , ""
    , "\nMetaData key\nString key"
    , ""
    , ""
    , "MediaSource source"
    , "List sources"
    , "List urls"
    , ""
    , ""
""
};

static const int qtscript_MediaObject_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_MediaObject_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("MediaObject::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::MediaObject*)
Q_DECLARE_METATYPE(QtScriptShell_MediaObject*)
Q_DECLARE_METATYPE(Phonon::MediaSource)
Q_DECLARE_METATYPE(QList<Phonon::MediaSource>)
Q_DECLARE_METATYPE(QList<QUrl>)
template <> \
struct QMetaTypeId< QMultiMap<QString,QString> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QMultiMap<QString,QString> >("QMultiMap<QString,QString>"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(Phonon::MetaData)
Q_DECLARE_METATYPE(Phonon::MediaNode*)

//
// MediaObject
//

static QScriptValue qtscript_MediaObject_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::MediaObject* _q_self = qscriptvalue_cast<Phonon::MediaObject*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("MediaObject.%0(): this object is not a MediaObject")
            .arg(qtscript_MediaObject_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clearQueue();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        Phonon::MediaSource _q_result = _q_self->currentSource();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->currentTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Phonon::MediaSource>() == context->argument(0).toVariant().userType())) {
            Phonon::MediaSource _q_arg0 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(0));
            _q_self->enqueue(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isArray()) {
            QList<Phonon::MediaSource> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->enqueue(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QList<QUrl> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->enqueue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        Phonon::ErrorType _q_result = _q_self->errorType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasVideo();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSeekable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QMultiMap<QString,QString> _q_result = _q_self->metaData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Phonon::MetaData>() == context->argument(0).toVariant().userType())) {
            Phonon::MetaData _q_arg0 = qscriptvalue_cast<Phonon::MetaData>(context->argument(0));
            QStringList _q_result = _q_self->metaData(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QStringList _q_result = _q_self->metaData(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QList<Phonon::MediaSource> _q_result = _q_self->queue();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->remainingTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        Phonon::MediaSource _q_arg0 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(0));
        _q_self->setCurrentSource(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QList<Phonon::MediaSource> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setQueue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QList<QUrl> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setQueue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        Phonon::State _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->totalTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("MediaObject");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaObject_throw_ambiguity_error_helper(context,
        qtscript_MediaObject_function_names[_id+1],
        qtscript_MediaObject_function_signatures[_id+1]);
}

static QScriptValue qtscript_MediaObject_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("MediaObject(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_MediaObject* _q_cpp_result = new QtScriptShell_MediaObject();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::MediaObject*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_MediaObject* _q_cpp_result = new QtScriptShell_MediaObject(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::MediaObject*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaObject_throw_ambiguity_error_helper(context,
        qtscript_MediaObject_function_names[_id],
        qtscript_MediaObject_function_signatures[_id]);
}

static QScriptValue qtscript_MediaObject_toScriptValue(QScriptEngine *engine, Phonon::MediaObject* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_MediaObject_fromScriptValue(const QScriptValue &value, Phonon::MediaObject* &out)
{
    out = qobject_cast<Phonon::MediaObject*>(value.toQObject());
}

QScriptValue qtscript_create_MediaObject_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaObject*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::MediaObject*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    proto.setProperty(QString::fromLatin1("__MediaNode__"),
        engine->defaultPrototype(qMetaTypeId<Phonon::MediaNode*>()),
        QScriptValue::SkipInEnumeration);
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_MediaObject_prototype_call, qtscript_MediaObject_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_MediaObject_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<Phonon::MediaObject*>(engine, qtscript_MediaObject_toScriptValue, 
        qtscript_MediaObject_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_MediaObject_static_call, proto, qtscript_MediaObject_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
