#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsignalmapper.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsignalmapper.h>

#include "qtscriptshell_QSignalMapper.h"

static const char * const qtscript_QSignalMapper_function_names[] = {
    "QSignalMapper"
    // static
    // prototype
    , "mappingById"
    , "mappingByObject"
    , "mappingByString"
    , "removeMappings"
    , "setMappingById"
    , "setMappingByObject"
    , "setMappingByString"
    , "toString"
};

static const char * const qtscript_QSignalMapper_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "int id"
    , "QObject object"
    , "String text"
    , "QObject sender"
    , "QObject sender, int id"
    , "QObject sender, QObject object"
    , "QObject sender, String text"
""
};

static const int qtscript_QSignalMapper_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 0
};

static QScriptValue qtscript_QSignalMapper_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSignalMapper::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSignalMapper*)
Q_DECLARE_METATYPE(QtScriptShell_QSignalMapper*)

//
// QSignalMapper
//

static QScriptValue qtscript_QSignalMapper_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSignalMapper* _q_self = qscriptvalue_cast<QSignalMapper*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSignalMapper.%0(): this object is not a QSignalMapper")
            .arg(qtscript_QSignalMapper_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QObject* _q_result = _q_self->mapping(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QObject* _q_result = _q_self->mapping(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_result = _q_self->mapping(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        _q_self->removeMappings(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setMapping(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QObject* _q_arg1 = context->argument(1).toQObject();
        _q_self->setMapping(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setMapping(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QSignalMapper");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSignalMapper_throw_ambiguity_error_helper(context,
        qtscript_QSignalMapper_function_names[_id+1],
        qtscript_QSignalMapper_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSignalMapper_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSignalMapper(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSignalMapper* _q_cpp_result = new QtScriptShell_QSignalMapper();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSignalMapper*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSignalMapper* _q_cpp_result = new QtScriptShell_QSignalMapper(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSignalMapper*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSignalMapper_throw_ambiguity_error_helper(context,
        qtscript_QSignalMapper_function_names[_id],
        qtscript_QSignalMapper_function_signatures[_id]);
}

static QScriptValue qtscript_QSignalMapper_toScriptValue(QScriptEngine *engine, QSignalMapper* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSignalMapper_fromScriptValue(const QScriptValue &value, QSignalMapper* &out)
{
    out = qobject_cast<QSignalMapper*>(value.toQObject());
}

QScriptValue qtscript_create_QSignalMapper_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSignalMapper*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSignalMapper*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSignalMapper_prototype_call, qtscript_QSignalMapper_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSignalMapper_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSignalMapper*>(engine, qtscript_QSignalMapper_toScriptValue, 
        qtscript_QSignalMapper_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSignalMapper_static_call, proto, qtscript_QSignalMapper_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
