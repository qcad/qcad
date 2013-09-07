#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qvalidator.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocale.h>
#include <qobject.h>
#include <qvalidator.h>

#include "qtscriptshell_QIntValidator.h"

static const char * const qtscript_QIntValidator_function_names[] = {
    "QIntValidator"
    // static
    // prototype
    , "setRange"
    , "toString"
};

static const char * const qtscript_QIntValidator_function_signatures[] = {
    "QObject parent\nint bottom, int top, QObject parent"
    // static
    // prototype
    , "int bottom, int top"
""
};

static const int qtscript_QIntValidator_function_lengths[] = {
    3
    // static
    // prototype
    , 2
    , 0
};

static QScriptValue qtscript_QIntValidator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QIntValidator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QIntValidator*)
Q_DECLARE_METATYPE(QtScriptShell_QIntValidator*)
Q_DECLARE_METATYPE(QValidator*)

//
// QIntValidator
//

static QScriptValue qtscript_QIntValidator_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QIntValidator* _q_self = qscriptvalue_cast<QIntValidator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QIntValidator.%0(): this object is not a QIntValidator")
            .arg(qtscript_QIntValidator_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QIntValidator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIntValidator_throw_ambiguity_error_helper(context,
        qtscript_QIntValidator_function_names[_id+1],
        qtscript_QIntValidator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QIntValidator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QIntValidator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QIntValidator* _q_cpp_result = new QtScriptShell_QIntValidator();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIntValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QIntValidator* _q_cpp_result = new QtScriptShell_QIntValidator(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIntValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QIntValidator* _q_cpp_result = new QtScriptShell_QIntValidator(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIntValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QObject* _q_arg2 = context->argument(2).toQObject();
        QtScriptShell_QIntValidator* _q_cpp_result = new QtScriptShell_QIntValidator(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QIntValidator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIntValidator_throw_ambiguity_error_helper(context,
        qtscript_QIntValidator_function_names[_id],
        qtscript_QIntValidator_function_signatures[_id]);
}

static QScriptValue qtscript_QIntValidator_toScriptValue(QScriptEngine *engine, QIntValidator* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QIntValidator_fromScriptValue(const QScriptValue &value, QIntValidator* &out)
{
    out = qobject_cast<QIntValidator*>(value.toQObject());
}

QScriptValue qtscript_create_QIntValidator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QIntValidator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QIntValidator*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QValidator*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QIntValidator_prototype_call, qtscript_QIntValidator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QIntValidator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QIntValidator*>(engine, qtscript_QIntValidator_toScriptValue, 
        qtscript_QIntValidator_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QIntValidator_static_call, proto, qtscript_QIntValidator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
