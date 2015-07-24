#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractnetworkcache.h>
#include <QVariant>
#include <qabstractnetworkcache.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qobject.h>
#include <qurl.h>

#include "qtscriptshell_QAbstractNetworkCache.h"

static const char * const qtscript_QAbstractNetworkCache_function_names[] = {
    "QAbstractNetworkCache"
    // static
    // prototype
    , "cacheSize"
    , "data"
    , "insert"
    , "metaData"
    , "prepare"
    , "remove"
    , "updateMetaData"
    , "toString"
};

static const char * const qtscript_QAbstractNetworkCache_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "QUrl url"
    , "QIODevice device"
    , "QUrl url"
    , "QNetworkCacheMetaData metaData"
    , "QUrl url"
    , "QNetworkCacheMetaData metaData"
""
};

static const int qtscript_QAbstractNetworkCache_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractNetworkCache_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractNetworkCache::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractNetworkCache*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractNetworkCache*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QNetworkCacheMetaData)

//
// QAbstractNetworkCache
//

static QScriptValue qtscript_QAbstractNetworkCache_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractNetworkCache* _q_self = qscriptvalue_cast<QAbstractNetworkCache*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractNetworkCache.%0(): this object is not a QAbstractNetworkCache")
            .arg(qtscript_QAbstractNetworkCache_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->cacheSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        QIODevice* _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->insert(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        QNetworkCacheMetaData _q_result = _q_self->metaData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QNetworkCacheMetaData _q_arg0 = qscriptvalue_cast<QNetworkCacheMetaData>(context->argument(0));
        QIODevice* _q_result = _q_self->prepare(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = _q_self->remove(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QNetworkCacheMetaData _q_arg0 = qscriptvalue_cast<QNetworkCacheMetaData>(context->argument(0));
        _q_self->updateMetaData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QAbstractNetworkCache");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractNetworkCache_throw_ambiguity_error_helper(context,
        qtscript_QAbstractNetworkCache_function_names[_id+1],
        qtscript_QAbstractNetworkCache_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractNetworkCache_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QAbstractNetworkCache cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractNetworkCache_throw_ambiguity_error_helper(context,
        qtscript_QAbstractNetworkCache_function_names[_id],
        qtscript_QAbstractNetworkCache_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractNetworkCache_toScriptValue(QScriptEngine *engine, QAbstractNetworkCache* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractNetworkCache_fromScriptValue(const QScriptValue &value, QAbstractNetworkCache* &out)
{
    out = qobject_cast<QAbstractNetworkCache*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractNetworkCache_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractNetworkCache*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractNetworkCache*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractNetworkCache_prototype_call, qtscript_QAbstractNetworkCache_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractNetworkCache_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractNetworkCache*>(engine, qtscript_QAbstractNetworkCache_toScriptValue, 
        qtscript_QAbstractNetworkCache_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractNetworkCache_static_call, proto, qtscript_QAbstractNetworkCache_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
