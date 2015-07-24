#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtemporaryfile.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfile.h>
#include <qlist.h>
#include <qobject.h>
#include <qtemporaryfile.h>

#include "qtscriptshell_QTemporaryFile.h"

static const char * const qtscript_QTemporaryFile_function_names[] = {
    "QTemporaryFile"
    // static
    , "createLocalFile"
    // prototype
    , "autoRemove"
    , "fileTemplate"
    , "open"
    , "setAutoRemove"
    , "setFileTemplate"
    , "uniqueFilename"
    , "toString"
};

static const char * const qtscript_QTemporaryFile_function_signatures[] = {
    "\nQObject parent\nString templateName\nString templateName, QObject parent"
    // static
    , "QFile file\nString fileName"
    // prototype
    , ""
    , ""
    , ""
    , "bool b"
    , "String name"
    , ""
""
};

static const int qtscript_QTemporaryFile_function_lengths[] = {
    2
    // static
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTemporaryFile_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTemporaryFile::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTemporaryFile*)
Q_DECLARE_METATYPE(QtScriptShell_QTemporaryFile*)
Q_DECLARE_METATYPE(QFile*)

//
// QTemporaryFile
//

static QScriptValue qtscript_QTemporaryFile_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTemporaryFile* _q_self = qscriptvalue_cast<QTemporaryFile*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTemporaryFile.%0(): this object is not a QTemporaryFile")
            .arg(qtscript_QTemporaryFile_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->autoRemove();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileTemplate();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->open();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAutoRemove(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileTemplate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QTemporaryFile");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTemporaryFile_throw_ambiguity_error_helper(context,
        qtscript_QTemporaryFile_function_names[_id+2],
        qtscript_QTemporaryFile_function_signatures[_id+2]);
}

static QScriptValue qtscript_QTemporaryFile_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTemporaryFile(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTemporaryFile* _q_cpp_result = new QtScriptShell_QTemporaryFile();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTemporaryFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QTemporaryFile* _q_cpp_result = new QtScriptShell_QTemporaryFile(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTemporaryFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QTemporaryFile* _q_cpp_result = new QtScriptShell_QTemporaryFile(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTemporaryFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QTemporaryFile* _q_cpp_result = new QtScriptShell_QTemporaryFile(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTemporaryFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QFile*>(context->argument(0))) {

        QFile & _q_arg0 = *qscriptvalue_cast<QFile*>(context->argument(0));
                    QTemporaryFile* _q_result = QTemporaryFile::createLocalFile(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QTemporaryFile* _q_result = QTemporaryFile::createLocalFile(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTemporaryFile_throw_ambiguity_error_helper(context,
        qtscript_QTemporaryFile_function_names[_id],
        qtscript_QTemporaryFile_function_signatures[_id]);
}

static QScriptValue qtscript_QTemporaryFile_toScriptValue(QScriptEngine *engine, QTemporaryFile* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTemporaryFile_fromScriptValue(const QScriptValue &value, QTemporaryFile* &out)
{
    out = qobject_cast<QTemporaryFile*>(value.toQObject());
}

QScriptValue qtscript_create_QTemporaryFile_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTemporaryFile*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTemporaryFile*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFile*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTemporaryFile_prototype_call, qtscript_QTemporaryFile_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTemporaryFile_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTemporaryFile*>(engine, qtscript_QTemporaryFile_toScriptValue, 
        qtscript_QTemporaryFile_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTemporaryFile_static_call, proto, qtscript_QTemporaryFile_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTemporaryFile_static_call,
            qtscript_QTemporaryFile_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QTemporaryFile_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
