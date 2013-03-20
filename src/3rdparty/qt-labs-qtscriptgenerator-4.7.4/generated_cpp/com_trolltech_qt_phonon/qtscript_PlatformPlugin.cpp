#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <platformplugin.h>
#include <QVariant>
#include <abstractmediastream.h>
#include <objectdescription.h>
#include <qbytearray.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>
#include <qpair.h>
#include <qstringlist.h>
#include <qurl.h>

#include "qtscriptshell_PlatformPlugin.h"

static const char * const qtscript_PlatformPlugin_function_names[] = {
    "PlatformPlugin"
    // static
    // prototype
    , "applicationName"
    , "createBackend"
    , "createMediaStream"
    , "deviceAccessListFor"
    , "icon"
    , "isMimeTypeAvailable"
    , "loadVolume"
    , "notification"
    , "objectDescriptionIndexes"
    , "objectDescriptionProperties"
    , "saveVolume"
    , "toString"
};

static const char * const qtscript_PlatformPlugin_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "\nString library, String version"
    , "QUrl url, QObject parent"
    , "AudioOutputDevice arg__1"
    , "String name"
    , "String mimeType"
    , "String outputName"
    , "char notificationName, String text, List actions, QObject receiver, char actionSlot"
    , "ObjectDescriptionType type"
    , "ObjectDescriptionType type, int index"
    , "String outputName, qreal volume"
""
};

static const int qtscript_PlatformPlugin_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 2
    , 2
    , 1
    , 1
    , 1
    , 1
    , 5
    , 1
    , 2
    , 2
    , 0
};

static QScriptValue qtscript_PlatformPlugin_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("PlatformPlugin::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::PlatformPlugin*)
Q_DECLARE_METATYPE(QtScriptShell_PlatformPlugin*)
Q_DECLARE_METATYPE(Phonon::AbstractMediaStream*)
template <> \
struct QMetaTypeId< QPair<QByteArray,QString> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<QByteArray,QString> >("QPair<QByteArray,QString>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<QByteArray,QString> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QList<QPair<QByteArray,QString> > >("QList<QPair<QByteArray,QString> >"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(Phonon::ObjectDescriptionType)
Q_DECLARE_METATYPE(QList<int>)
template <> \
struct QMetaTypeId< QHash<QByteArray,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QHash<QByteArray,QVariant> >("QHash<QByteArray,QVariant>"); \
        return metatype_id; \
    } \
};

//
// PlatformPlugin
//

static QScriptValue qtscript_PlatformPlugin_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::PlatformPlugin* _q_self = qscriptvalue_cast<Phonon::PlatformPlugin*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("PlatformPlugin.%0(): this object is not a PlatformPlugin")
            .arg(qtscript_PlatformPlugin_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->applicationName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->createBackend();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QObject* _q_result = _q_self->createBackend(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        Phonon::AbstractMediaStream* _q_result = _q_self->createMediaStream(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        Phonon::AudioOutputDevice _q_arg0 = qscriptvalue_cast<Phonon::AudioOutputDevice>(context->argument(0));
        QList<QPair<QByteArray,QString> > _q_result = _q_self->deviceAccessListFor(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QIcon _q_result = _q_self->icon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->isMimeTypeAvailable(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        qreal _q_result = _q_self->loadVolume(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QStringList _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        _q_self->notification(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QStringList _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QObject* _q_arg3 = context->argument(3).toQObject();
        _q_self->notification(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        char* _q_arg0 = qscriptvalue_cast<char*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QStringList _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QObject* _q_arg3 = context->argument(3).toQObject();
        char* _q_arg4 = qscriptvalue_cast<char*>(context->argument(4));
        _q_self->notification(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        Phonon::ObjectDescriptionType _q_arg0 = qscriptvalue_cast<Phonon::ObjectDescriptionType>(context->argument(0));
        QList<int> _q_result = _q_self->objectDescriptionIndexes(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        Phonon::ObjectDescriptionType _q_arg0 = qscriptvalue_cast<Phonon::ObjectDescriptionType>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QHash<QByteArray,QVariant> _q_result = _q_self->objectDescriptionProperties(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->saveVolume(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11: {
    QString result = QString::fromLatin1("PlatformPlugin");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_PlatformPlugin_throw_ambiguity_error_helper(context,
        qtscript_PlatformPlugin_function_names[_id+1],
        qtscript_PlatformPlugin_function_signatures[_id+1]);
}

static QScriptValue qtscript_PlatformPlugin_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("PlatformPlugin(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_PlatformPlugin* _q_cpp_result = new QtScriptShell_PlatformPlugin();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((Phonon::PlatformPlugin*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_PlatformPlugin_throw_ambiguity_error_helper(context,
        qtscript_PlatformPlugin_function_names[_id],
        qtscript_PlatformPlugin_function_signatures[_id]);
}

QScriptValue qtscript_create_PlatformPlugin_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::PlatformPlugin*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::PlatformPlugin*)0));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_PlatformPlugin_prototype_call, qtscript_PlatformPlugin_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_PlatformPlugin_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::PlatformPlugin*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_PlatformPlugin_static_call, proto, qtscript_PlatformPlugin_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
