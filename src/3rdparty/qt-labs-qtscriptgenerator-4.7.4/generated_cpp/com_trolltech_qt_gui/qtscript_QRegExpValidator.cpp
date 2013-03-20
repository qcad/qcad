#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qvalidator.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocale.h>
#include <qobject.h>
#include <qregexp.h>
#include <qvalidator.h>

#include "qtscriptshell_QRegExpValidator.h"

static const char * const qtscript_QRegExpValidator_function_names[] = {
    "QRegExpValidator"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QRegExpValidator_function_signatures[] = {
    "QObject parent\nQRegExp rx, QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QRegExpValidator_function_lengths[] = {
    2
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QRegExpValidator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRegExpValidator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRegExpValidator*)
Q_DECLARE_METATYPE(QtScriptShell_QRegExpValidator*)
Q_DECLARE_METATYPE(QValidator*)

//
// QRegExpValidator
//

static QScriptValue qtscript_QRegExpValidator_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QRegExpValidator* _q_self = qscriptvalue_cast<QRegExpValidator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRegExpValidator.%0(): this object is not a QRegExpValidator")
            .arg(qtscript_QRegExpValidator_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QRegExpValidator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRegExpValidator_throw_ambiguity_error_helper(context,
        qtscript_QRegExpValidator_function_names[_id+1],
        qtscript_QRegExpValidator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QRegExpValidator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRegExpValidator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QRegExpValidator* _q_cpp_result = new QtScriptShell_QRegExpValidator();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QRegExpValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QRegExpValidator* _q_cpp_result = new QtScriptShell_QRegExpValidator(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QRegExpValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QRegExp _q_arg0 = context->argument(0).toRegExp();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QRegExpValidator* _q_cpp_result = new QtScriptShell_QRegExpValidator(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QRegExpValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRegExpValidator_throw_ambiguity_error_helper(context,
        qtscript_QRegExpValidator_function_names[_id],
        qtscript_QRegExpValidator_function_signatures[_id]);
}

static QScriptValue qtscript_QRegExpValidator_toScriptValue(QScriptEngine *engine, QRegExpValidator* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QRegExpValidator_fromScriptValue(const QScriptValue &value, QRegExpValidator* &out)
{
    out = qobject_cast<QRegExpValidator*>(value.toQObject());
}

QScriptValue qtscript_create_QRegExpValidator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRegExpValidator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRegExpValidator*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QValidator*>()));

    qScriptRegisterMetaType<QRegExpValidator*>(engine, qtscript_QRegExpValidator_toScriptValue, 
        qtscript_QRegExpValidator_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRegExpValidator_static_call, proto, qtscript_QRegExpValidator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
