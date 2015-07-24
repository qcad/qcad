#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qnetworkdiskcache.h>
#include <QVariant>
#include <qabstractnetworkcache.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qnetworkdiskcache.h>
#include <qobject.h>
#include <qurl.h>

#include "qtscriptshell_QNetworkDiskCache.h"

static const char * const qtscript_QNetworkDiskCache_function_names[] = {
    "QNetworkDiskCache"
    // static
    // prototype
    , "cacheDirectory"
    , "fileMetaData"
    , "maximumCacheSize"
    , "setCacheDirectory"
    , "setMaximumCacheSize"
    , "toString"
};

static const char * const qtscript_QNetworkDiskCache_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "String fileName"
    , ""
    , "String cacheDir"
    , "qint64 size"
""
};

static const int qtscript_QNetworkDiskCache_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QNetworkDiskCache_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkDiskCache::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkDiskCache*)
Q_DECLARE_METATYPE(QtScriptShell_QNetworkDiskCache*)
Q_DECLARE_METATYPE(QNetworkCacheMetaData)
Q_DECLARE_METATYPE(QAbstractNetworkCache*)

//
// QNetworkDiskCache
//

static QScriptValue qtscript_QNetworkDiskCache_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkDiskCache* _q_self = qscriptvalue_cast<QNetworkDiskCache*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkDiskCache.%0(): this object is not a QNetworkDiskCache")
            .arg(qtscript_QNetworkDiskCache_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->cacheDirectory();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QNetworkCacheMetaData _q_result = _q_self->fileMetaData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->maximumCacheSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setCacheDirectory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setMaximumCacheSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QNetworkDiskCache");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkDiskCache_throw_ambiguity_error_helper(context,
        qtscript_QNetworkDiskCache_function_names[_id+1],
        qtscript_QNetworkDiskCache_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkDiskCache_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkDiskCache(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QNetworkDiskCache* _q_cpp_result = new QtScriptShell_QNetworkDiskCache();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QNetworkDiskCache*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QNetworkDiskCache* _q_cpp_result = new QtScriptShell_QNetworkDiskCache(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QNetworkDiskCache*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkDiskCache_throw_ambiguity_error_helper(context,
        qtscript_QNetworkDiskCache_function_names[_id],
        qtscript_QNetworkDiskCache_function_signatures[_id]);
}

static QScriptValue qtscript_QNetworkDiskCache_toScriptValue(QScriptEngine *engine, QNetworkDiskCache* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QNetworkDiskCache_fromScriptValue(const QScriptValue &value, QNetworkDiskCache* &out)
{
    out = qobject_cast<QNetworkDiskCache*>(value.toQObject());
}

QScriptValue qtscript_create_QNetworkDiskCache_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkDiskCache*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkDiskCache*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractNetworkCache*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkDiskCache_prototype_call, qtscript_QNetworkDiskCache_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkDiskCache_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QNetworkDiskCache*>(engine, qtscript_QNetworkDiskCache_toScriptValue, 
        qtscript_QNetworkDiskCache_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkDiskCache_static_call, proto, qtscript_QNetworkDiskCache_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
