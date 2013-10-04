#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qfileinfo.h>
#include <QDateTime>
#include <QDir>
#include <QVariant>
#include <qdatetime.h>
#include <qdir.h>
#include <qfile.h>
#include <qfileinfo.h>

static const char * const qtscript_QFileInfo_function_names[] = {
    "QFileInfo"
    // static
    // prototype
    , "absoluteDir"
    , "absoluteFilePath"
    , "absolutePath"
    , "baseName"
    , "bundleName"
    , "caching"
    , "canonicalFilePath"
    , "canonicalPath"
    , "completeBaseName"
    , "completeSuffix"
    , "created"
    , "dir"
    , "exists"
    , "fileName"
    , "filePath"
    , "group"
    , "groupId"
    , "isAbsolute"
    , "isBundle"
    , "isDir"
    , "isExecutable"
    , "isFile"
    , "isHidden"
    , "isReadable"
    , "isRelative"
    , "isRoot"
    , "isSymLink"
    , "isWritable"
    , "lastModified"
    , "lastRead"
    , "makeAbsolute"
    , "equals"
    , "owner"
    , "ownerId"
    , "path"
    , "permission"
    , "permissions"
    , "refresh"
    , "setCaching"
    , "setFile"
    , "size"
    , "suffix"
    , "symLinkTarget"
    , "toString"
};

static const char * const qtscript_QFileInfo_function_signatures[] = {
    "\nQDir dir, String file\nQFile file\nQFileInfo fileinfo\nString file"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QFileInfo fileinfo"
    , ""
    , ""
    , ""
    , "Permissions permissions"
    , ""
    , ""
    , "bool on"
    , "QDir dir, String file\nQFile file\nString file"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QFileInfo_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 2
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QFileInfo_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFileInfo::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFileInfo)
Q_DECLARE_METATYPE(QFileInfo*)
Q_DECLARE_METATYPE(QDir)
Q_DECLARE_METATYPE(QFlags<QFile::Permission>)
Q_DECLARE_METATYPE(QFile*)

//
// QFileInfo
//

static QScriptValue qtscript_QFileInfo_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 43;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFileInfo* _q_self = qscriptvalue_cast<QFileInfo*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFileInfo.%0(): this object is not a QFileInfo")
            .arg(qtscript_QFileInfo_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QDir _q_result = _q_self->absoluteDir();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->absoluteFilePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->absolutePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->baseName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->bundleName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->caching();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->canonicalFilePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->canonicalPath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->completeBaseName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->completeSuffix();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->created();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QDir _q_result = _q_self->dir();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exists();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->filePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->group();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->groupId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAbsolute();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isBundle();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDir();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isExecutable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFile();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isHidden();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isReadable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRelative();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRoot();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSymLink();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWritable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->lastModified();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->lastRead();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->makeAbsolute();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QFileInfo _q_arg0 = qscriptvalue_cast<QFileInfo>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->owner();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->ownerId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->path();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QFlags<QFile::Permission> _q_arg0 = qscriptvalue_cast<QFlags<QFile::Permission> >(context->argument(0));
        bool _q_result = _q_self->permission(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QFlags<QFile::Permission> _q_result = _q_self->permissions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        _q_self->refresh();
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setCaching(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QFile*>(context->argument(0))) {

        QFile & _q_arg0 = *qscriptvalue_cast<QFile*>(context->argument(0));
                    _q_self->setFile(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setFile(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setFile(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->suffix();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->symLinkTarget();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 43: {
    QString result = QString::fromLatin1("QFileInfo");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileInfo_throw_ambiguity_error_helper(context,
        qtscript_QFileInfo_function_names[_id+1],
        qtscript_QFileInfo_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFileInfo_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFileInfo(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QFileInfo _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QFile*>(context->argument(0))) {

        QFile & _q_arg0 = *qscriptvalue_cast<QFile*>(context->argument(0));
                    QFileInfo _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QFileInfo>() == context->argument(0).toVariant().userType())) {
            QFileInfo _q_arg0 = qscriptvalue_cast<QFileInfo>(context->argument(0));
            QFileInfo _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QFileInfo _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QFileInfo _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileInfo_throw_ambiguity_error_helper(context,
        qtscript_QFileInfo_function_names[_id],
        qtscript_QFileInfo_function_signatures[_id]);
}

QScriptValue qtscript_create_QFileInfo_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFileInfo*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFileInfo*)0));
    for (int i = 0; i < 44; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFileInfo_prototype_call, qtscript_QFileInfo_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFileInfo_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QFileInfo>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QFileInfo*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFileInfo_static_call, proto, qtscript_QFileInfo_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
