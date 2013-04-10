#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractmessagehandler.h>
#include <QVariant>
#include <qabstractmessagehandler.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsourcelocation.h>
#include <qurl.h>

#include "qtscriptshell_QAbstractMessageHandler.h"

static const char * const qtscript_QAbstractMessageHandler_function_names[] = {
    "QAbstractMessageHandler"
    // static
    // prototype
    , "message"
    , "toString"
};

static const char * const qtscript_QAbstractMessageHandler_function_signatures[] = {
    ""
    // static
    // prototype
    , "QtMsgType type, String description, QUrl identifier, QSourceLocation sourceLocation"
""
};

static const int qtscript_QAbstractMessageHandler_function_lengths[] = {
    0
    // static
    // prototype
    , 4
    , 0
};

static QScriptValue qtscript_QAbstractMessageHandler_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractMessageHandler::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractMessageHandler*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractMessageHandler*)
Q_DECLARE_METATYPE(QtMsgType)

//
// QAbstractMessageHandler
//

static QScriptValue qtscript_QAbstractMessageHandler_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractMessageHandler* _q_self = qscriptvalue_cast<QAbstractMessageHandler*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractMessageHandler.%0(): this object is not a QAbstractMessageHandler")
            .arg(qtscript_QAbstractMessageHandler_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QtMsgType _q_arg0 = qscriptvalue_cast<QtMsgType>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->message(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QtMsgType _q_arg0 = qscriptvalue_cast<QtMsgType>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QUrl _q_arg2 = qscriptvalue_cast<QUrl>(context->argument(2));
        _q_self->message(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QtMsgType _q_arg0 = qscriptvalue_cast<QtMsgType>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QUrl _q_arg2 = qscriptvalue_cast<QUrl>(context->argument(2));
        QSourceLocation _q_arg3 = qscriptvalue_cast<QSourceLocation>(context->argument(3));
        _q_self->message(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QAbstractMessageHandler");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractMessageHandler_throw_ambiguity_error_helper(context,
        qtscript_QAbstractMessageHandler_function_names[_id+1],
        qtscript_QAbstractMessageHandler_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractMessageHandler_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QAbstractMessageHandler cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractMessageHandler_throw_ambiguity_error_helper(context,
        qtscript_QAbstractMessageHandler_function_names[_id],
        qtscript_QAbstractMessageHandler_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractMessageHandler_toScriptValue(QScriptEngine *engine, QAbstractMessageHandler* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractMessageHandler_fromScriptValue(const QScriptValue &value, QAbstractMessageHandler* &out)
{
    out = qobject_cast<QAbstractMessageHandler*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractMessageHandler_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractMessageHandler*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractMessageHandler*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractMessageHandler_prototype_call, qtscript_QAbstractMessageHandler_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractMessageHandler_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractMessageHandler*>(engine, qtscript_QAbstractMessageHandler_toScriptValue, 
        qtscript_QAbstractMessageHandler_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractMessageHandler_static_call, proto, qtscript_QAbstractMessageHandler_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
