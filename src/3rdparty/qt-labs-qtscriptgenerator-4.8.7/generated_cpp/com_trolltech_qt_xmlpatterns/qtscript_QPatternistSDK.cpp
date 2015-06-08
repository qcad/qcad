#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlnamepool.h>
#include <QVariant>


static const char * const qtscript_QPatternistSDK_function_names[] = {
    "QPatternistSDK"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QPatternistSDK_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QPatternistSDK_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QPatternistSDK_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPatternistSDK::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}


//
// QPatternistSDK
//

static QScriptValue qtscript_QPatternistSDK_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QPatternistSDK cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPatternistSDK_throw_ambiguity_error_helper(context,
        qtscript_QPatternistSDK_function_names[_id],
        qtscript_QPatternistSDK_function_signatures[_id]);
}

QScriptValue qtscript_create_QPatternistSDK_class(QScriptEngine *engine)
{
    QScriptValue proto = QScriptValue();
    QScriptValue ctor = engine->newFunction(qtscript_QPatternistSDK_static_call, proto, qtscript_QPatternistSDK_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
