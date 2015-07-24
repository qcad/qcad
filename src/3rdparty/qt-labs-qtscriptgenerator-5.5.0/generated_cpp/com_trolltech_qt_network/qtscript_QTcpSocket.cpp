#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtcpsocket.h>
#include <QVariant>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>
#include <qtcpsocket.h>

#include "qtscriptshell_QTcpSocket.h"

static const char * const qtscript_QTcpSocket_function_names[] = {
    "QTcpSocket"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QTcpSocket_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QTcpSocket_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QTcpSocket_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTcpSocket::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTcpSocket*)
Q_DECLARE_METATYPE(QtScriptShell_QTcpSocket*)
Q_DECLARE_METATYPE(QAbstractSocket*)

//
// QTcpSocket
//

static QScriptValue qtscript_QTcpSocket_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTcpSocket* _q_self = qscriptvalue_cast<QTcpSocket*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTcpSocket.%0(): this object is not a QTcpSocket")
            .arg(qtscript_QTcpSocket_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QTcpSocket");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTcpSocket_throw_ambiguity_error_helper(context,
        qtscript_QTcpSocket_function_names[_id+1],
        qtscript_QTcpSocket_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTcpSocket_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTcpSocket(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTcpSocket* _q_cpp_result = new QtScriptShell_QTcpSocket();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTcpSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QTcpSocket* _q_cpp_result = new QtScriptShell_QTcpSocket(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTcpSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTcpSocket_throw_ambiguity_error_helper(context,
        qtscript_QTcpSocket_function_names[_id],
        qtscript_QTcpSocket_function_signatures[_id]);
}

static QScriptValue qtscript_QTcpSocket_toScriptValue(QScriptEngine *engine, QTcpSocket* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTcpSocket_fromScriptValue(const QScriptValue &value, QTcpSocket* &out)
{
    out = qobject_cast<QTcpSocket*>(value.toQObject());
}

QScriptValue qtscript_create_QTcpSocket_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTcpSocket*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTcpSocket*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractSocket*>()));

    qScriptRegisterMetaType<QTcpSocket*>(engine, qtscript_QTcpSocket_toScriptValue, 
        qtscript_QTcpSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTcpSocket_static_call, proto, qtscript_QTcpSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
