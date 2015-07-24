#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <backendinterface.h>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

#include "qtscriptshell_AbstractBackend.h"

static const char * const qtscript_AbstractBackend_function_names[] = {
    "AbstractBackend"
    // static
    // prototype
    , "availableMimeTypes"
    , "connectNodes"
    , "createObject"
    , "disconnectNodes"
    , "endConnectionChange"
    , "objectDescriptionIndexes"
    , "objectDescriptionProperties"
    , "startConnectionChange"
    , "toString"
};

static const char * const qtscript_AbstractBackend_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "QObject arg__1, QObject arg__2"
    , "Class c, QObject parent, List args"
    , "QObject arg__1, QObject arg__2"
    , "Set arg__1"
    , "ObjectDescriptionType type"
    , "ObjectDescriptionType type, int index"
    , "Set arg__1"
""
};

static const int qtscript_AbstractBackend_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 2
    , 3
    , 2
    , 1
    , 1
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_AbstractBackend_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractBackend::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::BackendInterface*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractBackend*)
Q_DECLARE_METATYPE(Phonon::BackendInterface::Class)
Q_DECLARE_METATYPE(QSet<QObject*>)
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
// Phonon::BackendInterface::Class
//

static const Phonon::BackendInterface::Class qtscript_AbstractBackend_Class_values[] = {
    Phonon::BackendInterface::MediaObjectClass
    , Phonon::BackendInterface::VolumeFaderEffectClass
    , Phonon::BackendInterface::AudioOutputClass
    , Phonon::BackendInterface::AudioDataOutputClass
    , Phonon::BackendInterface::VisualizationClass
    , Phonon::BackendInterface::VideoDataOutputClass
    , Phonon::BackendInterface::EffectClass
    , Phonon::BackendInterface::VideoWidgetClass
};

static const char * const qtscript_AbstractBackend_Class_keys[] = {
    "MediaObjectClass"
    , "VolumeFaderEffectClass"
    , "AudioOutputClass"
    , "AudioDataOutputClass"
    , "VisualizationClass"
    , "VideoDataOutputClass"
    , "EffectClass"
    , "VideoWidgetClass"
};

static QString qtscript_AbstractBackend_Class_toStringHelper(Phonon::BackendInterface::Class value)
{
    if ((value >= Phonon::BackendInterface::MediaObjectClass) && (value <= Phonon::BackendInterface::VideoWidgetClass))
        return qtscript_AbstractBackend_Class_keys[static_cast<int>(value)-static_cast<int>(Phonon::BackendInterface::MediaObjectClass)];
    return QString();
}

static QScriptValue qtscript_AbstractBackend_Class_toScriptValue(QScriptEngine *engine, const Phonon::BackendInterface::Class &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("AbstractBackend"));
    return clazz.property(qtscript_AbstractBackend_Class_toStringHelper(value));
}

static void qtscript_AbstractBackend_Class_fromScriptValue(const QScriptValue &value, Phonon::BackendInterface::Class &out)
{
    out = qvariant_cast<Phonon::BackendInterface::Class>(value.toVariant());
}

static QScriptValue qtscript_construct_AbstractBackend_Class(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Phonon::BackendInterface::MediaObjectClass) && (arg <= Phonon::BackendInterface::VideoWidgetClass))
        return qScriptValueFromValue(engine,  static_cast<Phonon::BackendInterface::Class>(arg));
    return context->throwError(QString::fromLatin1("Class(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_AbstractBackend_Class_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::BackendInterface::Class value = qscriptvalue_cast<Phonon::BackendInterface::Class>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_AbstractBackend_Class_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::BackendInterface::Class value = qscriptvalue_cast<Phonon::BackendInterface::Class>(context->thisObject());
    return QScriptValue(engine, qtscript_AbstractBackend_Class_toStringHelper(value));
}

static QScriptValue qtscript_create_AbstractBackend_Class_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_AbstractBackend_Class,
        qtscript_AbstractBackend_Class_valueOf, qtscript_AbstractBackend_Class_toString);
    qScriptRegisterMetaType<Phonon::BackendInterface::Class>(engine, qtscript_AbstractBackend_Class_toScriptValue,
        qtscript_AbstractBackend_Class_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_AbstractBackend_Class_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_AbstractBackend_Class_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// AbstractBackend
//

static QScriptValue qtscript_AbstractBackend_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::BackendInterface* _q_self = qscriptvalue_cast<Phonon::BackendInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractBackend.%0(): this object is not a AbstractBackend")
            .arg(qtscript_AbstractBackend_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->availableMimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QObject* _q_arg1 = context->argument(1).toQObject();
        bool _q_result = _q_self->connectNodes(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        Phonon::BackendInterface::Class _q_arg0 = qscriptvalue_cast<Phonon::BackendInterface::Class>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QList<QVariant> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QObject* _q_result = _q_self->createObject(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QObject* _q_arg1 = context->argument(1).toQObject();
        bool _q_result = _q_self->disconnectNodes(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QSet<QObject*> _q_arg0 = qscriptvalue_cast<QSet<QObject*> >(context->argument(0));
        bool _q_result = _q_self->endConnectionChange(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        Phonon::ObjectDescriptionType _q_arg0 = qscriptvalue_cast<Phonon::ObjectDescriptionType>(context->argument(0));
        QList<int> _q_result = _q_self->objectDescriptionIndexes(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        Phonon::ObjectDescriptionType _q_arg0 = qscriptvalue_cast<Phonon::ObjectDescriptionType>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QHash<QByteArray,QVariant> _q_result = _q_self->objectDescriptionProperties(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QSet<QObject*> _q_arg0 = qscriptvalue_cast<QSet<QObject*> >(context->argument(0));
        bool _q_result = _q_self->startConnectionChange(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("AbstractBackend");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractBackend_throw_ambiguity_error_helper(context,
        qtscript_AbstractBackend_function_names[_id+1],
        qtscript_AbstractBackend_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractBackend_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AbstractBackend(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_AbstractBackend* _q_cpp_result = new QtScriptShell_AbstractBackend();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((Phonon::BackendInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractBackend_throw_ambiguity_error_helper(context,
        qtscript_AbstractBackend_function_names[_id],
        qtscript_AbstractBackend_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractBackend_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::BackendInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::BackendInterface*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AbstractBackend_prototype_call, qtscript_AbstractBackend_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AbstractBackend_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::BackendInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractBackend_static_call, proto, qtscript_AbstractBackend_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Class"),
        qtscript_create_AbstractBackend_Class_class(engine, ctor));
    return ctor;
}
