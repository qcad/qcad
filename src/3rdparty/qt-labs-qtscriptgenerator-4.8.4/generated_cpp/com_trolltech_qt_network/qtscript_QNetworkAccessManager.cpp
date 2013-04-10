#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qnetworkaccessmanager.h>
#include <QVariant>
#include <qabstractnetworkcache.h>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qnetworkcookiejar.h>
#include <qnetworkproxy.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qsslerror.h>

#include "qtscriptshell_QNetworkAccessManager.h"

static const char * const qtscript_QNetworkAccessManager_function_names[] = {
    "QNetworkAccessManager"
    // static
    // prototype
    , "cache"
    , "cookieJar"
    , "deleteResource"
    , "get"
    , "head"
    , "post"
    , "proxy"
    , "proxyFactory"
    , "put"
    , "sendCustomRequest"
    , "setCache"
    , "setCookieJar"
    , "setProxy"
    , "setProxyFactory"
    , "toString"
};

static const char * const qtscript_QNetworkAccessManager_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , ""
    , "QNetworkRequest request"
    , "QNetworkRequest request"
    , "QNetworkRequest request"
    , "QNetworkRequest request, QIODevice data\nQNetworkRequest request, QByteArray data"
    , ""
    , ""
    , "QNetworkRequest request, QIODevice data\nQNetworkRequest request, QByteArray data"
    , "QNetworkRequest request, QByteArray verb, QIODevice data"
    , "QAbstractNetworkCache cache"
    , "QNetworkCookieJar cookieJar"
    , "QNetworkProxy proxy"
    , "QNetworkProxyFactory factory"
""
};

static const int qtscript_QNetworkAccessManager_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 1
    , 2
    , 0
    , 0
    , 2
    , 3
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QNetworkAccessManager_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkAccessManager::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkAccessManager*)
Q_DECLARE_METATYPE(QtScriptShell_QNetworkAccessManager*)
Q_DECLARE_METATYPE(QNetworkAccessManager::NetworkAccessibility)
Q_DECLARE_METATYPE(QNetworkAccessManager::Operation)
Q_DECLARE_METATYPE(QAbstractNetworkCache*)
Q_DECLARE_METATYPE(QNetworkCookieJar*)
Q_DECLARE_METATYPE(QNetworkReply*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QNetworkProxy)
Q_DECLARE_METATYPE(QNetworkProxyFactory*)

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
// QNetworkAccessManager::NetworkAccessibility
//

static const QNetworkAccessManager::NetworkAccessibility qtscript_QNetworkAccessManager_NetworkAccessibility_values[] = {
    QNetworkAccessManager::UnknownAccessibility
    , QNetworkAccessManager::NotAccessible
    , QNetworkAccessManager::Accessible
};

static const char * const qtscript_QNetworkAccessManager_NetworkAccessibility_keys[] = {
    "UnknownAccessibility"
    , "NotAccessible"
    , "Accessible"
};

static QString qtscript_QNetworkAccessManager_NetworkAccessibility_toStringHelper(QNetworkAccessManager::NetworkAccessibility value)
{
    if ((value >= QNetworkAccessManager::UnknownAccessibility) && (value <= QNetworkAccessManager::Accessible))
        return qtscript_QNetworkAccessManager_NetworkAccessibility_keys[static_cast<int>(value)-static_cast<int>(QNetworkAccessManager::UnknownAccessibility)];
    return QString();
}

static QScriptValue qtscript_QNetworkAccessManager_NetworkAccessibility_toScriptValue(QScriptEngine *engine, const QNetworkAccessManager::NetworkAccessibility &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkAccessManager"));
    return clazz.property(qtscript_QNetworkAccessManager_NetworkAccessibility_toStringHelper(value));
}

static void qtscript_QNetworkAccessManager_NetworkAccessibility_fromScriptValue(const QScriptValue &value, QNetworkAccessManager::NetworkAccessibility &out)
{
    out = qvariant_cast<QNetworkAccessManager::NetworkAccessibility>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkAccessManager_NetworkAccessibility(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QNetworkAccessManager::UnknownAccessibility) && (arg <= QNetworkAccessManager::Accessible))
        return qScriptValueFromValue(engine,  static_cast<QNetworkAccessManager::NetworkAccessibility>(arg));
    return context->throwError(QString::fromLatin1("NetworkAccessibility(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkAccessManager_NetworkAccessibility_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkAccessManager::NetworkAccessibility value = qscriptvalue_cast<QNetworkAccessManager::NetworkAccessibility>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkAccessManager_NetworkAccessibility_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkAccessManager::NetworkAccessibility value = qscriptvalue_cast<QNetworkAccessManager::NetworkAccessibility>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkAccessManager_NetworkAccessibility_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkAccessManager_NetworkAccessibility_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkAccessManager_NetworkAccessibility,
        qtscript_QNetworkAccessManager_NetworkAccessibility_valueOf, qtscript_QNetworkAccessManager_NetworkAccessibility_toString);
    qScriptRegisterMetaType<QNetworkAccessManager::NetworkAccessibility>(engine, qtscript_QNetworkAccessManager_NetworkAccessibility_toScriptValue,
        qtscript_QNetworkAccessManager_NetworkAccessibility_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkAccessManager_NetworkAccessibility_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkAccessManager_NetworkAccessibility_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkAccessManager::Operation
//

static const QNetworkAccessManager::Operation qtscript_QNetworkAccessManager_Operation_values[] = {
    QNetworkAccessManager::UnknownOperation
    , QNetworkAccessManager::HeadOperation
    , QNetworkAccessManager::GetOperation
    , QNetworkAccessManager::PutOperation
    , QNetworkAccessManager::PostOperation
    , QNetworkAccessManager::DeleteOperation
    , QNetworkAccessManager::CustomOperation
};

static const char * const qtscript_QNetworkAccessManager_Operation_keys[] = {
    "UnknownOperation"
    , "HeadOperation"
    , "GetOperation"
    , "PutOperation"
    , "PostOperation"
    , "DeleteOperation"
    , "CustomOperation"
};

static QString qtscript_QNetworkAccessManager_Operation_toStringHelper(QNetworkAccessManager::Operation value)
{
    if ((value >= QNetworkAccessManager::UnknownOperation) && (value <= QNetworkAccessManager::CustomOperation))
        return qtscript_QNetworkAccessManager_Operation_keys[static_cast<int>(value)-static_cast<int>(QNetworkAccessManager::UnknownOperation)];
    return QString();
}

static QScriptValue qtscript_QNetworkAccessManager_Operation_toScriptValue(QScriptEngine *engine, const QNetworkAccessManager::Operation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkAccessManager"));
    return clazz.property(qtscript_QNetworkAccessManager_Operation_toStringHelper(value));
}

static void qtscript_QNetworkAccessManager_Operation_fromScriptValue(const QScriptValue &value, QNetworkAccessManager::Operation &out)
{
    out = qvariant_cast<QNetworkAccessManager::Operation>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkAccessManager_Operation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QNetworkAccessManager::UnknownOperation) && (arg <= QNetworkAccessManager::CustomOperation))
        return qScriptValueFromValue(engine,  static_cast<QNetworkAccessManager::Operation>(arg));
    return context->throwError(QString::fromLatin1("Operation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkAccessManager_Operation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkAccessManager::Operation value = qscriptvalue_cast<QNetworkAccessManager::Operation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkAccessManager_Operation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkAccessManager::Operation value = qscriptvalue_cast<QNetworkAccessManager::Operation>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkAccessManager_Operation_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkAccessManager_Operation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkAccessManager_Operation,
        qtscript_QNetworkAccessManager_Operation_valueOf, qtscript_QNetworkAccessManager_Operation_toString);
    qScriptRegisterMetaType<QNetworkAccessManager::Operation>(engine, qtscript_QNetworkAccessManager_Operation_toScriptValue,
        qtscript_QNetworkAccessManager_Operation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkAccessManager_Operation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkAccessManager_Operation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkAccessManager
//

static QScriptValue qtscript_QNetworkAccessManager_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkAccessManager* _q_self = qscriptvalue_cast<QNetworkAccessManager*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkAccessManager.%0(): this object is not a QNetworkAccessManager")
            .arg(qtscript_QNetworkAccessManager_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QAbstractNetworkCache* _q_result = _q_self->cache();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QNetworkCookieJar* _q_result = _q_self->cookieJar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        QNetworkReply* _q_result = _q_self->deleteResource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        QNetworkReply* _q_result = _q_self->get(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        QNetworkReply* _q_result = _q_self->head(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QNetworkRequest>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QIODevice*>(context->argument(1))) {
            QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            QNetworkReply* _q_result = _q_self->post(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QNetworkRequest>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QNetworkReply* _q_result = _q_self->post(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QNetworkProxy _q_result = _q_self->proxy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QNetworkProxyFactory* _q_result = _q_self->proxyFactory();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QNetworkRequest>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QIODevice*>(context->argument(1))) {
            QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            QNetworkReply* _q_result = _q_self->put(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QNetworkRequest>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QNetworkReply* _q_result = _q_self->put(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QNetworkReply* _q_result = _q_self->sendCustomRequest(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QIODevice* _q_arg2 = qscriptvalue_cast<QIODevice*>(context->argument(2));
        QNetworkReply* _q_result = _q_self->sendCustomRequest(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QAbstractNetworkCache* _q_arg0 = qscriptvalue_cast<QAbstractNetworkCache*>(context->argument(0));
        _q_self->setCache(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QNetworkCookieJar* _q_arg0 = qscriptvalue_cast<QNetworkCookieJar*>(context->argument(0));
        _q_self->setCookieJar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QNetworkProxy _q_arg0 = qscriptvalue_cast<QNetworkProxy>(context->argument(0));
        _q_self->setProxy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QNetworkProxyFactory* _q_arg0 = qscriptvalue_cast<QNetworkProxyFactory*>(context->argument(0));
        _q_self->setProxyFactory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QNetworkAccessManager");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkAccessManager_throw_ambiguity_error_helper(context,
        qtscript_QNetworkAccessManager_function_names[_id+1],
        qtscript_QNetworkAccessManager_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkAccessManager_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkAccessManager(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QNetworkAccessManager* _q_cpp_result = new QtScriptShell_QNetworkAccessManager();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QNetworkAccessManager*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QNetworkAccessManager* _q_cpp_result = new QtScriptShell_QNetworkAccessManager(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QNetworkAccessManager*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkAccessManager_throw_ambiguity_error_helper(context,
        qtscript_QNetworkAccessManager_function_names[_id],
        qtscript_QNetworkAccessManager_function_signatures[_id]);
}

static QScriptValue qtscript_QNetworkAccessManager_toScriptValue(QScriptEngine *engine, QNetworkAccessManager* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QNetworkAccessManager_fromScriptValue(const QScriptValue &value, QNetworkAccessManager* &out)
{
    out = qobject_cast<QNetworkAccessManager*>(value.toQObject());
}

QScriptValue qtscript_create_QNetworkAccessManager_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkAccessManager*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkAccessManager*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkAccessManager_prototype_call, qtscript_QNetworkAccessManager_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkAccessManager_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QNetworkAccessManager*>(engine, qtscript_QNetworkAccessManager_toScriptValue, 
        qtscript_QNetworkAccessManager_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkAccessManager_static_call, proto, qtscript_QNetworkAccessManager_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("NetworkAccessibility"),
        qtscript_create_QNetworkAccessManager_NetworkAccessibility_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Operation"),
        qtscript_create_QNetworkAccessManager_Operation_class(engine, ctor));
    return ctor;
}
