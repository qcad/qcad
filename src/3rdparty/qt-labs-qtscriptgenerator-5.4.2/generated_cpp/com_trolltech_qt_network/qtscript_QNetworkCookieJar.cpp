#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qnetworkcookiejar.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qnetworkcookie.h>
#include <qnetworkcookiejar.h>
#include <qobject.h>
#include <qurl.h>

#include "qtscriptshell_QNetworkCookieJar.h"

static const char * const qtscript_QNetworkCookieJar_function_names[] = {
    "QNetworkCookieJar"
    // static
    // prototype
    , "cookiesForUrl"
    , "deleteCookie"
    , "insertCookie"
    , "setCookiesFromUrl"
    , "updateCookie"
    , "toString"
};

static const char * const qtscript_QNetworkCookieJar_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QUrl url"
    , "QNetworkCookie cookie"
    , "QNetworkCookie cookie"
    , "List cookieList, QUrl url"
    , "QNetworkCookie cookie"
""
};

static const int qtscript_QNetworkCookieJar_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QNetworkCookieJar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkCookieJar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkCookieJar*)
Q_DECLARE_METATYPE(QtScriptShell_QNetworkCookieJar*)
Q_DECLARE_METATYPE(QList<QNetworkCookie >)

//
// QNetworkCookieJar
//

static QScriptValue qtscript_QNetworkCookieJar_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QNetworkCookieJar* _q_self = qscriptvalue_cast<QNetworkCookieJar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkCookieJar.%0(): this object is not a QNetworkCookieJar")
            .arg(qtscript_QNetworkCookieJar_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        QList<QNetworkCookie > _q_result = _q_self->cookiesForUrl(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QNetworkCookie _q_arg0 = qscriptvalue_cast<QNetworkCookie>(context->argument(0));
        bool _q_result = _q_self->deleteCookie(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QNetworkCookie _q_arg0 = qscriptvalue_cast<QNetworkCookie>(context->argument(0));
        bool _q_result = _q_self->insertCookie(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QList<QNetworkCookie> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
        bool _q_result = _q_self->setCookiesFromUrl(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QNetworkCookie _q_arg0 = qscriptvalue_cast<QNetworkCookie>(context->argument(0));
        bool _q_result = _q_self->updateCookie(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QNetworkCookieJar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkCookieJar_throw_ambiguity_error_helper(context,
        qtscript_QNetworkCookieJar_function_names[_id+1],
        qtscript_QNetworkCookieJar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkCookieJar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QNetworkCookieJar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QNetworkCookieJar* _q_cpp_result = new QtScriptShell_QNetworkCookieJar();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QNetworkCookieJar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QNetworkCookieJar* _q_cpp_result = new QtScriptShell_QNetworkCookieJar(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QNetworkCookieJar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkCookieJar_throw_ambiguity_error_helper(context,
        qtscript_QNetworkCookieJar_function_names[_id],
        qtscript_QNetworkCookieJar_function_signatures[_id]);
}

static QScriptValue qtscript_QNetworkCookieJar_toScriptValue(QScriptEngine *engine, QNetworkCookieJar* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QNetworkCookieJar_fromScriptValue(const QScriptValue &value, QNetworkCookieJar* &out)
{
    out = qobject_cast<QNetworkCookieJar*>(value.toQObject());
}

QScriptValue qtscript_create_QNetworkCookieJar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkCookieJar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkCookieJar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkCookieJar_prototype_call, qtscript_QNetworkCookieJar_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkCookieJar_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QNetworkCookieJar*>(engine, qtscript_QNetworkCookieJar_toScriptValue, 
        qtscript_QNetworkCookieJar_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkCookieJar_static_call, proto, qtscript_QNetworkCookieJar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
