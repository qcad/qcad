#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpropertyanimation.h>
#include <QVariant>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qeasingcurve.h>
#include <qlist.h>
#include <qobject.h>
#include <qpair.h>
#include <qpropertyanimation.h>
#include <qvector.h>

#include "qtscriptshell_QPropertyAnimation.h"

static const char * const qtscript_QPropertyAnimation_function_names[] = {
    "QPropertyAnimation"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QPropertyAnimation_function_signatures[] = {
    "QObject parent\nQObject target, QByteArray propertyName, QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QPropertyAnimation_function_lengths[] = {
    3
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QPropertyAnimation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPropertyAnimation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPropertyAnimation*)
Q_DECLARE_METATYPE(QtScriptShell_QPropertyAnimation*)
Q_DECLARE_METATYPE(QVariantAnimation*)

//
// QPropertyAnimation
//

static QScriptValue qtscript_QPropertyAnimation_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPropertyAnimation* _q_self = qscriptvalue_cast<QPropertyAnimation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPropertyAnimation.%0(): this object is not a QPropertyAnimation")
            .arg(qtscript_QPropertyAnimation_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QPropertyAnimation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPropertyAnimation_throw_ambiguity_error_helper(context,
        qtscript_QPropertyAnimation_function_names[_id+1],
        qtscript_QPropertyAnimation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPropertyAnimation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPropertyAnimation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPropertyAnimation* _q_cpp_result = new QtScriptShell_QPropertyAnimation();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPropertyAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QPropertyAnimation* _q_cpp_result = new QtScriptShell_QPropertyAnimation(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPropertyAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();

          // TEMPLATE - core.convert_string_arg_to_latin1 - START
          QByteArray _q_arg1 = context->argument(1).toString().toLatin1();
    // TEMPLATE - core.convert_string_arg_to_latin1 - END
                QtScriptShell_QPropertyAnimation* _q_cpp_result = new QtScriptShell_QPropertyAnimation(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPropertyAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QObject* _q_arg0 = context->argument(0).toQObject();

          // TEMPLATE - core.convert_string_arg_to_latin1 - START
          QByteArray _q_arg1 = context->argument(1).toString().toLatin1();
    // TEMPLATE - core.convert_string_arg_to_latin1 - END
                QObject* _q_arg2 = context->argument(2).toQObject();
        QtScriptShell_QPropertyAnimation* _q_cpp_result = new QtScriptShell_QPropertyAnimation(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPropertyAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPropertyAnimation_throw_ambiguity_error_helper(context,
        qtscript_QPropertyAnimation_function_names[_id],
        qtscript_QPropertyAnimation_function_signatures[_id]);
}

static QScriptValue qtscript_QPropertyAnimation_toScriptValue(QScriptEngine *engine, QPropertyAnimation* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPropertyAnimation_fromScriptValue(const QScriptValue &value, QPropertyAnimation* &out)
{
    out = qobject_cast<QPropertyAnimation*>(value.toQObject());
}

QScriptValue qtscript_create_QPropertyAnimation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPropertyAnimation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPropertyAnimation*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QVariantAnimation*>()));

    qScriptRegisterMetaType<QPropertyAnimation*>(engine, qtscript_QPropertyAnimation_toScriptValue, 
        qtscript_QPropertyAnimation_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPropertyAnimation_static_call, proto, qtscript_QPropertyAnimation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
