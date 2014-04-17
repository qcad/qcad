#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qpictureformatplugin.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpicture.h>

#include "qtscriptshell_QPictureFormatPlugin.h"

static const char * const qtscript_QPictureFormatPlugin_function_names[] = {
    "QPictureFormatPlugin"
    // static
    // prototype
    , "installIOHandler"
    , "loadPicture"
    , "savePicture"
    , "toString"
};

static const char * const qtscript_QPictureFormatPlugin_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String format"
    , "String format, String filename, QPicture pic"
    , "String format, String filename, QPicture pic"
""
};

static const int qtscript_QPictureFormatPlugin_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 3
    , 3
    , 0
};

static QScriptValue qtscript_QPictureFormatPlugin_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPictureFormatPlugin::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPictureFormatPlugin*)
Q_DECLARE_METATYPE(QtScriptShell_QPictureFormatPlugin*)
Q_DECLARE_METATYPE(QPicture*)
Q_DECLARE_METATYPE(QPicture)

//
// QPictureFormatPlugin
//

static QScriptValue qtscript_QPictureFormatPlugin_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPictureFormatPlugin* _q_self = qscriptvalue_cast<QPictureFormatPlugin*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPictureFormatPlugin.%0(): this object is not a QPictureFormatPlugin")
            .arg(qtscript_QPictureFormatPlugin_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->installIOHandler(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QPicture* _q_arg2 = qscriptvalue_cast<QPicture*>(context->argument(2));
        bool _q_result = _q_self->loadPicture(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QPicture _q_arg2 = qscriptvalue_cast<QPicture>(context->argument(2));
        bool _q_result = _q_self->savePicture(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QPictureFormatPlugin");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPictureFormatPlugin_throw_ambiguity_error_helper(context,
        qtscript_QPictureFormatPlugin_function_names[_id+1],
        qtscript_QPictureFormatPlugin_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPictureFormatPlugin_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPictureFormatPlugin(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPictureFormatPlugin* _q_cpp_result = new QtScriptShell_QPictureFormatPlugin();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPictureFormatPlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QPictureFormatPlugin* _q_cpp_result = new QtScriptShell_QPictureFormatPlugin(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPictureFormatPlugin*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPictureFormatPlugin_throw_ambiguity_error_helper(context,
        qtscript_QPictureFormatPlugin_function_names[_id],
        qtscript_QPictureFormatPlugin_function_signatures[_id]);
}

static QScriptValue qtscript_QPictureFormatPlugin_toScriptValue(QScriptEngine *engine, QPictureFormatPlugin* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPictureFormatPlugin_fromScriptValue(const QScriptValue &value, QPictureFormatPlugin* &out)
{
    out = qobject_cast<QPictureFormatPlugin*>(value.toQObject());
}

QScriptValue qtscript_create_QPictureFormatPlugin_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPictureFormatPlugin*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPictureFormatPlugin*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPictureFormatPlugin_prototype_call, qtscript_QPictureFormatPlugin_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPictureFormatPlugin_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QPictureFormatPlugin*>(engine, qtscript_QPictureFormatPlugin_toScriptValue, 
        qtscript_QPictureFormatPlugin_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPictureFormatPlugin_static_call, proto, qtscript_QPictureFormatPlugin_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
