#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractnetworkcache.h>
#include <QDateTime>
#include <QVariant>
#include <qabstractnetworkcache.h>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qdatetime.h>
#include <qlist.h>
#include <qpair.h>
#include <qurl.h>

static const char * const qtscript_QNetworkCacheMetaData_function_names[] = {
    "QNetworkCacheMetaData"
    // static
    // prototype
    , "attributes"
    , "expirationDate"
    , "isValid"
    , "lastModified"
    , "equals"
    , "rawHeaders"
    , "readFrom"
    , "saveToDisk"
    , "setAttributes"
    , "setExpirationDate"
    , "setLastModified"
    , "setRawHeaders"
    , "setSaveToDisk"
    , "setUrl"
    , "url"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QNetworkCacheMetaData_function_signatures[] = {
    "\nQNetworkCacheMetaData other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QNetworkCacheMetaData other"
    , ""
    , "QDataStream arg__1"
    , ""
    , "HashMap attributes"
    , "QDateTime dateTime"
    , "QDateTime dateTime"
    , "List headers"
    , "bool allow"
    , "QUrl url"
    , ""
    , "QDataStream arg__1"
""
};

static const int qtscript_QNetworkCacheMetaData_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QNetworkCacheMetaData_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkCacheMetaData::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkCacheMetaData)
Q_DECLARE_METATYPE(QNetworkCacheMetaData*)
Q_DECLARE_METATYPE(QNetworkRequest::Attribute)
template <> \
struct QMetaTypeId< QHash<QNetworkRequest::Attribute,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QHash<QNetworkRequest::Attribute,QVariant> >("QHash<QNetworkRequest::Attribute,QVariant>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QPair<QByteArray,QByteArray> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<QByteArray,QByteArray> >("QPair<QByteArray,QByteArray>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<QByteArray,QByteArray> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QList<QPair<QByteArray,QByteArray> > >("QList<QPair<QByteArray,QByteArray> >"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(QDataStream*)

//
// QNetworkCacheMetaData
//

static QScriptValue qtscript_QNetworkCacheMetaData_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 16;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkCacheMetaData* _q_self = qscriptvalue_cast<QNetworkCacheMetaData*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkCacheMetaData.%0(): this object is not a QNetworkCacheMetaData")
            .arg(qtscript_QNetworkCacheMetaData_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QHash<QNetworkRequest::Attribute,QVariant> _q_result = _q_self->attributes();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->expirationDate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->lastModified();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QNetworkCacheMetaData _q_arg0 = qscriptvalue_cast<QNetworkCacheMetaData>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QList<QPair<QByteArray,QByteArray> > _q_result = _q_self->rawHeaders();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->saveToDisk();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QHash<QNetworkRequest::Attribute,QVariant> _q_arg0 = qscriptvalue_cast<QHash<QNetworkRequest::Attribute,QVariant> >(context->argument(0));
        _q_self->setAttributes(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QDateTime _q_arg0 = context->argument(0).toDateTime();
        _q_self->setExpirationDate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QDateTime _q_arg0 = context->argument(0).toDateTime();
        _q_self->setLastModified(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QList<QPair<QByteArray,QByteArray> > _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setRawHeaders(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSaveToDisk(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->setUrl(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->url();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 16: {
    QString result = QString::fromLatin1("QNetworkCacheMetaData");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkCacheMetaData_throw_ambiguity_error_helper(context,
        qtscript_QNetworkCacheMetaData_function_names[_id+1],
        qtscript_QNetworkCacheMetaData_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkCacheMetaData_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkCacheMetaData(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QNetworkCacheMetaData _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QNetworkCacheMetaData _q_arg0 = qscriptvalue_cast<QNetworkCacheMetaData>(context->argument(0));
        QNetworkCacheMetaData _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkCacheMetaData_throw_ambiguity_error_helper(context,
        qtscript_QNetworkCacheMetaData_function_names[_id],
        qtscript_QNetworkCacheMetaData_function_signatures[_id]);
}

QScriptValue qtscript_create_QNetworkCacheMetaData_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkCacheMetaData*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkCacheMetaData*)0));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkCacheMetaData_prototype_call, qtscript_QNetworkCacheMetaData_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkCacheMetaData_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QNetworkCacheMetaData>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QNetworkCacheMetaData*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkCacheMetaData_static_call, proto, qtscript_QNetworkCacheMetaData_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
