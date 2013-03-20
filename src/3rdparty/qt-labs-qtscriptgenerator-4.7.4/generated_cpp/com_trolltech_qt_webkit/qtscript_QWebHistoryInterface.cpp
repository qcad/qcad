#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwebhistoryinterface.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qwebhistoryinterface.h>

#include "qtscriptshell_QWebHistoryInterface.h"

static const char * const qtscript_QWebHistoryInterface_function_names[] = {
    "QWebHistoryInterface"
    // static
    , "defaultInterface"
    , "setDefaultInterface"
    // prototype
    , "addHistoryEntry"
    , "historyContains"
    , "toString"
};

static const char * const qtscript_QWebHistoryInterface_function_signatures[] = {
    "QObject parent"
    // static
    , ""
    , "QWebHistoryInterface defaultInterface"
    // prototype
    , "String url"
    , "String url"
""
};

static const int qtscript_QWebHistoryInterface_function_lengths[] = {
    1
    // static
    , 0
    , 1
    // prototype
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QWebHistoryInterface_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebHistoryInterface::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebHistoryInterface*)
Q_DECLARE_METATYPE(QtScriptShell_QWebHistoryInterface*)

//
// QWebHistoryInterface
//

static QScriptValue qtscript_QWebHistoryInterface_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWebHistoryInterface* _q_self = qscriptvalue_cast<QWebHistoryInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebHistoryInterface.%0(): this object is not a QWebHistoryInterface")
            .arg(qtscript_QWebHistoryInterface_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->addHistoryEntry(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->historyContains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QWebHistoryInterface");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebHistoryInterface_throw_ambiguity_error_helper(context,
        qtscript_QWebHistoryInterface_function_names[_id+3],
        qtscript_QWebHistoryInterface_function_signatures[_id+3]);
}

static QScriptValue qtscript_QWebHistoryInterface_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebHistoryInterface(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWebHistoryInterface* _q_cpp_result = new QtScriptShell_QWebHistoryInterface();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWebHistoryInterface*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QWebHistoryInterface* _q_cpp_result = new QtScriptShell_QWebHistoryInterface(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWebHistoryInterface*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWebHistoryInterface* _q_result = QWebHistoryInterface::defaultInterface();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWebHistoryInterface* _q_arg0 = qscriptvalue_cast<QWebHistoryInterface*>(context->argument(0));
        QWebHistoryInterface::setDefaultInterface(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebHistoryInterface_throw_ambiguity_error_helper(context,
        qtscript_QWebHistoryInterface_function_names[_id],
        qtscript_QWebHistoryInterface_function_signatures[_id]);
}

static QScriptValue qtscript_QWebHistoryInterface_toScriptValue(QScriptEngine *engine, QWebHistoryInterface* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWebHistoryInterface_fromScriptValue(const QScriptValue &value, QWebHistoryInterface* &out)
{
    out = qobject_cast<QWebHistoryInterface*>(value.toQObject());
}

QScriptValue qtscript_create_QWebHistoryInterface_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebHistoryInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebHistoryInterface*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebHistoryInterface_prototype_call, qtscript_QWebHistoryInterface_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebHistoryInterface_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWebHistoryInterface*>(engine, qtscript_QWebHistoryInterface_toScriptValue, 
        qtscript_QWebHistoryInterface_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebHistoryInterface_static_call, proto, qtscript_QWebHistoryInterface_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebHistoryInterface_static_call,
            qtscript_QWebHistoryInterface_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QWebHistoryInterface_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
