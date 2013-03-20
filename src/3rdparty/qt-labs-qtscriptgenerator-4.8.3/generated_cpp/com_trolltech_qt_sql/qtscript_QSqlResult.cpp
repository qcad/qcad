#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsqlresult.h>
#include <QSize>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlrecord.h>
#include <qsqlresult.h>
#include <qvector.h>

#include "qtscriptshell_QSqlResult.h"

static const char * const qtscript_QSqlResult_function_names[] = {
    "QSqlResult"
    // static
    // prototype
    , "handle"
    , "toString"
};

static const char * const qtscript_QSqlResult_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
""
};

static const int qtscript_QSqlResult_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QSqlResult_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlResult::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlResult*)
Q_DECLARE_METATYPE(QtScriptShell_QSqlResult*)

//
// QSqlResult
//

static QScriptValue qtscript_QSqlResult_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSqlResult* _q_self = qscriptvalue_cast<QSqlResult*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlResult.%0(): this object is not a QSqlResult")
            .arg(qtscript_QSqlResult_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->handle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QSqlResult");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlResult_throw_ambiguity_error_helper(context,
        qtscript_QSqlResult_function_names[_id+1],
        qtscript_QSqlResult_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlResult_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QSqlResult cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlResult_throw_ambiguity_error_helper(context,
        qtscript_QSqlResult_function_names[_id],
        qtscript_QSqlResult_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlResult_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlResult*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlResult*)0));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlResult_prototype_call, qtscript_QSqlResult_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlResult_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlResult*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlResult_static_call, proto, qtscript_QSqlResult_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
