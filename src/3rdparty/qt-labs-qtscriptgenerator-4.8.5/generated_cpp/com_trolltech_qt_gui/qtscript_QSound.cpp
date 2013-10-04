#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsound.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QSound.h"

static const char * const qtscript_QSound_function_names[] = {
    "QSound"
    // static
    , "isAvailable"
    , "play"
    // prototype
    , "fileName"
    , "isFinished"
    , "loops"
    , "loopsRemaining"
    , "setLoops"
    , "toString"
};

static const char * const qtscript_QSound_function_signatures[] = {
    "String filename, QObject parent"
    // static
    , ""
    , "String filename"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "int arg__1"
""
};

static const int qtscript_QSound_function_lengths[] = {
    2
    // static
    , 0
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QSound_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSound::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSound*)
Q_DECLARE_METATYPE(QtScriptShell_QSound*)

//
// QSound
//

static QScriptValue qtscript_QSound_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSound* _q_self = qscriptvalue_cast<QSound*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSound.%0(): this object is not a QSound")
            .arg(qtscript_QSound_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFinished();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loops();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loopsRemaining();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLoops(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QSound");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSound_throw_ambiguity_error_helper(context,
        qtscript_QSound_function_names[_id+3],
        qtscript_QSound_function_signatures[_id+3]);
}

static QScriptValue qtscript_QSound_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSound(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QtScriptShell_QSound* _q_cpp_result = new QtScriptShell_QSound(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSound*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QSound* _q_cpp_result = new QtScriptShell_QSound(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSound*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QSound::isAvailable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSound::play(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSound_throw_ambiguity_error_helper(context,
        qtscript_QSound_function_names[_id],
        qtscript_QSound_function_signatures[_id]);
}

static QScriptValue qtscript_QSound_toScriptValue(QScriptEngine *engine, QSound* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSound_fromScriptValue(const QScriptValue &value, QSound* &out)
{
    out = qobject_cast<QSound*>(value.toQObject());
}

QScriptValue qtscript_create_QSound_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSound*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSound*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSound_prototype_call, qtscript_QSound_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSound_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSound*>(engine, qtscript_QSound_toScriptValue, 
        qtscript_QSound_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSound_static_call, proto, qtscript_QSound_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSound_static_call,
            qtscript_QSound_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSound_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
