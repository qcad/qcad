#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qfilesystemwatcher.h>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>

#include "qtscriptshell_QFileSystemWatcher.h"

static const char * const qtscript_QFileSystemWatcher_function_names[] = {
    "QFileSystemWatcher"
    // static
    // prototype
    , "addPath"
    , "addPaths"
    , "directories"
    , "files"
    , "removePath"
    , "removePaths"
    , "toString"
};

static const char * const qtscript_QFileSystemWatcher_function_signatures[] = {
    "QObject parent\nList paths, QObject parent"
    // static
    // prototype
    , "String file"
    , "List files"
    , ""
    , ""
    , "String file"
    , "List files"
""
};

static const int qtscript_QFileSystemWatcher_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QFileSystemWatcher_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFileSystemWatcher::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFileSystemWatcher*)
Q_DECLARE_METATYPE(QtScriptShell_QFileSystemWatcher*)

//
// QFileSystemWatcher
//

static QScriptValue qtscript_QFileSystemWatcher_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFileSystemWatcher* _q_self = qscriptvalue_cast<QFileSystemWatcher*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFileSystemWatcher.%0(): this object is not a QFileSystemWatcher")
            .arg(qtscript_QFileSystemWatcher_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->addPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->addPaths(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->directories();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->files();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removePath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->removePaths(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QFileSystemWatcher");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileSystemWatcher_throw_ambiguity_error_helper(context,
        qtscript_QFileSystemWatcher_function_names[_id+1],
        qtscript_QFileSystemWatcher_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFileSystemWatcher_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFileSystemWatcher(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFileSystemWatcher* _q_cpp_result = new QtScriptShell_QFileSystemWatcher();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileSystemWatcher*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QFileSystemWatcher* _q_cpp_result = new QtScriptShell_QFileSystemWatcher(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileSystemWatcher*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isArray()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QtScriptShell_QFileSystemWatcher* _q_cpp_result = new QtScriptShell_QFileSystemWatcher(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileSystemWatcher*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QFileSystemWatcher* _q_cpp_result = new QtScriptShell_QFileSystemWatcher(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFileSystemWatcher*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileSystemWatcher_throw_ambiguity_error_helper(context,
        qtscript_QFileSystemWatcher_function_names[_id],
        qtscript_QFileSystemWatcher_function_signatures[_id]);
}

static QScriptValue qtscript_QFileSystemWatcher_toScriptValue(QScriptEngine *engine, QFileSystemWatcher* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFileSystemWatcher_fromScriptValue(const QScriptValue &value, QFileSystemWatcher* &out)
{
    out = qobject_cast<QFileSystemWatcher*>(value.toQObject());
}

QScriptValue qtscript_create_QFileSystemWatcher_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFileSystemWatcher*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFileSystemWatcher*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFileSystemWatcher_prototype_call, qtscript_QFileSystemWatcher_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFileSystemWatcher_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFileSystemWatcher*>(engine, qtscript_QFileSystemWatcher_toScriptValue, 
        qtscript_QFileSystemWatcher_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFileSystemWatcher_static_call, proto, qtscript_QFileSystemWatcher_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
