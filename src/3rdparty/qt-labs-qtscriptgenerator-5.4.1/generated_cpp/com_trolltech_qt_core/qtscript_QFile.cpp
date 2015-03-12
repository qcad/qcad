#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qfile.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfile.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QFile.h"

static const char * const qtscript_QFile_function_names[] = {
    "QFile"
    // static
    , "copy"
    , "decodeName"
    , "encodeName"
    , "exists"
    , "link"
    , "permissions"
    , "readLink"
    , "remove"
    , "rename"
    , "resize"
    , "setPermissions"
    , "symLinkTarget"
    // prototype
    , "copy"
    , "exists"
    , "link"
    , "open"
    , "close"
    , "readLink"
    , "remove"
    , "rename"
    , "setFileName"
    , "symLinkTarget"
    , "toString"
};

static const char * const qtscript_QFile_function_signatures[] = {
    "\nQObject parent\nString name\nString name, QObject parent"
    // static
    , "String fileName, String newName"
    , "QByteArray localFileName"
    , "String fileName"
    , "String fileName"
    , "String oldname, String newName"
    , "String filename"
    , "String fileName"
    , "String fileName"
    , "String oldName, String newName"
    , "String filename, qint64 sz"
    , "String filename, Permissions permissionSpec"
    , "String fileName"
    // prototype
    , "String newName"
    , ""
    , "String newName"
    , "int fd, OpenMode ioFlags, FileHandleFlags handleFlags"
    , ""
    , ""
    , ""
    , "String newName"
    , "String name"
    , ""
""
};

static const int qtscript_QFile_function_lengths[] = {
    2
    // static
    , 2
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 1
    // prototype
    , 1
    , 0
    , 1
    , 3
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QFile_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFile::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFile*)
Q_DECLARE_METATYPE(QtScriptShell_QFile*)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(QFlags<QFileDevice::FileHandleFlag>)
Q_DECLARE_METATYPE(QFlags<QFileDevice::Permission>)
Q_DECLARE_METATYPE(QFileDevice*)

//
// QFile
//

static QScriptValue qtscript_QFile_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFile* _q_self = qscriptvalue_cast<QFile*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFile.%0(): this object is not a QFile")
            .arg(qtscript_QFile_function_names[_id+13]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->copy(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exists();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->link(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QFlags<QIODevice::OpenModeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(0));
        bool _q_result = _q_self->open(_q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QFlags<QIODevice::OpenModeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(1));
        bool _q_result = _q_self->open(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QFlags<QIODevice::OpenModeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(1));
        QFlags<QFileDevice::FileHandleFlag> _q_arg2 = qscriptvalue_cast<QFlags<QFileDevice::FileHandleFlag> >(context->argument(2));
        bool _q_result = _q_self->open(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->close();
        return QScriptValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->readLink();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->remove();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->rename(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->symLinkTarget();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QFile");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFile_throw_ambiguity_error_helper(context,
        qtscript_QFile_function_names[_id+13],
        qtscript_QFile_function_signatures[_id+13]);
}

static QScriptValue qtscript_QFile_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFile(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QFile* _q_cpp_result = new QtScriptShell_QFile(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFile*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = QFile::copy(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_result = QFile::decodeName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = QFile::encodeName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QFile::exists(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = QFile::link(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QFileDevice::Permission> _q_result = QFile::permissions(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QFile::readLink(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QFile::remove(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = QFile::rename(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        qint64 _q_arg1 = qscriptvalue_cast<qint64>(context->argument(1));
        bool _q_result = QFile::resize(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QFileDevice::Permission> _q_arg1 = qscriptvalue_cast<QFlags<QFileDevice::Permission> >(context->argument(1));
        bool _q_result = QFile::setPermissions(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QFile::symLinkTarget(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFile_throw_ambiguity_error_helper(context,
        qtscript_QFile_function_names[_id],
        qtscript_QFile_function_signatures[_id]);
}

static QScriptValue qtscript_QFile_toScriptValue(QScriptEngine *engine, QFile* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFile_fromScriptValue(const QScriptValue &value, QFile* &out)
{
    out = qobject_cast<QFile*>(value.toQObject());
}

QScriptValue qtscript_create_QFile_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFile*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFile*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFileDevice*>()));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFile_prototype_call, qtscript_QFile_function_lengths[i+13]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFile_function_names[i+13]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFile*>(engine, qtscript_QFile_toScriptValue, 
        qtscript_QFile_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFile_static_call, proto, qtscript_QFile_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFile_static_call,
            qtscript_QFile_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QFile_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
