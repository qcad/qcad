#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdir.h>
#include <QVariant>
#include <qdir.h>
#include <qfileinfo.h>
#include <qlist.h>
#include <qstringlist.h>

static const char * const qtscript_QDir_function_names[] = {
    "QDir"
    // static
    , "addSearchPath"
    , "cleanPath"
    , "current"
    , "currentPath"
    , "drives"
    , "fromNativeSeparators"
    , "home"
    , "homePath"
    , "isAbsolutePath"
    , "isRelativePath"
    , "match"
    , "nameFiltersFromString"
    , "root"
    , "rootPath"
    , "searchPaths"
    , "separator"
    , "setCurrent"
    , "setSearchPaths"
    , "temp"
    , "tempPath"
    , "toNativeSeparators"
    // prototype
    , "absoluteFilePath"
    , "absolutePath"
    , "canonicalPath"
    , "cd"
    , "cdUp"
    , "count"
    , "dirName"
    , "entryInfoList"
    , "entryList"
    , "exists"
    , "filePath"
    , "filter"
    , "isAbsolute"
    , "isReadable"
    , "isRelative"
    , "isRoot"
    , "makeAbsolute"
    , "mkdir"
    , "mkpath"
    , "nameFilters"
    , "equals"
    , "operator_subscript"
    , "path"
    , "refresh"
    , "relativeFilePath"
    , "remove"
    , "removeRecursively"
    , "rename"
    , "rmdir"
    , "rmpath"
    , "setFilter"
    , "setNameFilters"
    , "setPath"
    , "setSorting"
    , "sorting"
    , "swap"
    , "toString"
};

static const char * const qtscript_QDir_function_signatures[] = {
    "QDir arg__1\nString path\nString path, String nameFilter, SortFlags sort, Filters filter"
    // static
    , "String prefix, String path"
    , "String path"
    , ""
    , ""
    , ""
    , "String pathName"
    , ""
    , ""
    , "String path"
    , "String path"
    , "String filter, String fileName\nList filters, String fileName"
    , "String nameFilter"
    , ""
    , ""
    , "String prefix"
    , ""
    , "String path"
    , "String prefix, List searchPaths"
    , ""
    , ""
    , "String pathName"
    // prototype
    , "String fileName"
    , ""
    , ""
    , "String dirName"
    , ""
    , ""
    , ""
    , "Filters filters, SortFlags sort\nList nameFilters, Filters filters, SortFlags sort"
    , "Filters filters, SortFlags sort\nList nameFilters, Filters filters, SortFlags sort"
    , "\nString name"
    , "String fileName"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String dirName"
    , "String dirPath"
    , ""
    , "QDir dir"
    , "int arg__1"
    , ""
    , ""
    , "String fileName"
    , "String fileName"
    , ""
    , "String oldName, String newName"
    , "String dirName"
    , "String dirPath"
    , "Filters filter"
    , "List nameFilters"
    , "String path"
    , "SortFlags sort"
    , ""
    , "QDir other"
""
};

static const int qtscript_QDir_function_lengths[] = {
    4
    // static
    , 2
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 2
    , 1
    , 0
    , 0
    , 1
    , 0
    , 1
    , 2
    , 0
    , 0
    , 1
    // prototype
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 3
    , 3
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QDir_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDir::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDir)
Q_DECLARE_METATYPE(QDir*)
Q_DECLARE_METATYPE(QDir::SortFlag)
Q_DECLARE_METATYPE(QFlags<QDir::SortFlag>)
Q_DECLARE_METATYPE(QDir::Filter)
Q_DECLARE_METATYPE(QFlags<QDir::Filter>)
Q_DECLARE_METATYPE(QList<QFileInfo >)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QDir::SortFlag
//

static const QDir::SortFlag qtscript_QDir_SortFlag_values[] = {
    QDir::NoSort
    , QDir::Name
    , QDir::Time
    , QDir::Size
    , QDir::Unsorted
    , QDir::DirsFirst
    , QDir::Reversed
    , QDir::IgnoreCase
    , QDir::DirsLast
    , QDir::LocaleAware
    , QDir::Type
};

static const char * const qtscript_QDir_SortFlag_keys[] = {
    "NoSort"
    , "Name"
    , "Time"
    , "Size"
    , "Unsorted"
    , "DirsFirst"
    , "Reversed"
    , "IgnoreCase"
    , "DirsLast"
    , "LocaleAware"
    , "Type"
};

static QString qtscript_QDir_SortFlag_toStringHelper(QDir::SortFlag value)
{
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QDir_SortFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QDir_SortFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QDir_SortFlag_toScriptValue(QScriptEngine *engine, const QDir::SortFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDir"));
    return clazz.property(qtscript_QDir_SortFlag_toStringHelper(value));
}

static void qtscript_QDir_SortFlag_fromScriptValue(const QScriptValue &value, QDir::SortFlag &out)
{
    out = qvariant_cast<QDir::SortFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QDir_SortFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QDir_SortFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QDir::SortFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("SortFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDir_SortFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDir::SortFlag value = qscriptvalue_cast<QDir::SortFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDir_SortFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDir::SortFlag value = qscriptvalue_cast<QDir::SortFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QDir_SortFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QDir_SortFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDir_SortFlag,
        qtscript_QDir_SortFlag_valueOf, qtscript_QDir_SortFlag_toString);
    qScriptRegisterMetaType<QDir::SortFlag>(engine, qtscript_QDir_SortFlag_toScriptValue,
        qtscript_QDir_SortFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDir_SortFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDir_SortFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDir::SortFlags
//

static QScriptValue qtscript_QDir_SortFlags_toScriptValue(QScriptEngine *engine, const QDir::SortFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QDir_SortFlags_fromScriptValue(const QScriptValue &value, QDir::SortFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QDir::SortFlags>())
        out = qvariant_cast<QDir::SortFlags>(var);
    else if (var.userType() == qMetaTypeId<QDir::SortFlag>())
        out = qvariant_cast<QDir::SortFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QDir_SortFlags(QScriptContext *context, QScriptEngine *engine)
{
    QDir::SortFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QDir::SortFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QDir::SortFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("SortFlags(): argument %0 is not of type SortFlag").arg(i));
            }
            result |= qvariant_cast<QDir::SortFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QDir_SortFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDir::SortFlags value = qscriptvalue_cast<QDir::SortFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDir_SortFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDir::SortFlags value = qscriptvalue_cast<QDir::SortFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 11; ++i) {
        if ((value & qtscript_QDir_SortFlag_values[i]) == qtscript_QDir_SortFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QDir_SortFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QDir_SortFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QDir::SortFlags>() == otherObj.value<QDir::SortFlags>())));
}

static QScriptValue qtscript_create_QDir_SortFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QDir_SortFlags, qtscript_QDir_SortFlags_valueOf,
        qtscript_QDir_SortFlags_toString, qtscript_QDir_SortFlags_equals);
    qScriptRegisterMetaType<QDir::SortFlags>(engine, qtscript_QDir_SortFlags_toScriptValue,
        qtscript_QDir_SortFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QDir::Filter
//

static const QDir::Filter qtscript_QDir_Filter_values[] = {
    QDir::NoFilter
    , QDir::Dirs
    , QDir::Files
    , QDir::Drives
    , QDir::AllEntries
    , QDir::NoSymLinks
    , QDir::TypeMask
    , QDir::Readable
    , QDir::Writable
    , QDir::Executable
    , QDir::PermissionMask
    , QDir::Modified
    , QDir::Hidden
    , QDir::System
    , QDir::AccessMask
    , QDir::AllDirs
    , QDir::CaseSensitive
    , QDir::NoDot
    , QDir::NoDotDot
    , QDir::NoDotAndDotDot
};

static const char * const qtscript_QDir_Filter_keys[] = {
    "NoFilter"
    , "Dirs"
    , "Files"
    , "Drives"
    , "AllEntries"
    , "NoSymLinks"
    , "TypeMask"
    , "Readable"
    , "Writable"
    , "Executable"
    , "PermissionMask"
    , "Modified"
    , "Hidden"
    , "System"
    , "AccessMask"
    , "AllDirs"
    , "CaseSensitive"
    , "NoDot"
    , "NoDotDot"
    , "NoDotAndDotDot"
};

static QString qtscript_QDir_Filter_toStringHelper(QDir::Filter value)
{
    for (int i = 0; i < 20; ++i) {
        if (qtscript_QDir_Filter_values[i] == value)
            return QString::fromLatin1(qtscript_QDir_Filter_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QDir_Filter_toScriptValue(QScriptEngine *engine, const QDir::Filter &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDir"));
    return clazz.property(qtscript_QDir_Filter_toStringHelper(value));
}

static void qtscript_QDir_Filter_fromScriptValue(const QScriptValue &value, QDir::Filter &out)
{
    out = qvariant_cast<QDir::Filter>(value.toVariant());
}

static QScriptValue qtscript_construct_QDir_Filter(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 20; ++i) {
        if (qtscript_QDir_Filter_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QDir::Filter>(arg));
    }
    return context->throwError(QString::fromLatin1("Filter(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDir_Filter_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDir::Filter value = qscriptvalue_cast<QDir::Filter>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDir_Filter_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDir::Filter value = qscriptvalue_cast<QDir::Filter>(context->thisObject());
    return QScriptValue(engine, qtscript_QDir_Filter_toStringHelper(value));
}

static QScriptValue qtscript_create_QDir_Filter_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDir_Filter,
        qtscript_QDir_Filter_valueOf, qtscript_QDir_Filter_toString);
    qScriptRegisterMetaType<QDir::Filter>(engine, qtscript_QDir_Filter_toScriptValue,
        qtscript_QDir_Filter_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 20; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDir_Filter_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDir_Filter_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDir::Filters
//

static QScriptValue qtscript_QDir_Filters_toScriptValue(QScriptEngine *engine, const QDir::Filters &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QDir_Filters_fromScriptValue(const QScriptValue &value, QDir::Filters &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QDir::Filters>())
        out = qvariant_cast<QDir::Filters>(var);
    else if (var.userType() == qMetaTypeId<QDir::Filter>())
        out = qvariant_cast<QDir::Filter>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QDir_Filters(QScriptContext *context, QScriptEngine *engine)
{
    QDir::Filters result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QDir::Filters>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QDir::Filter>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Filters(): argument %0 is not of type Filter").arg(i));
            }
            result |= qvariant_cast<QDir::Filter>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QDir_Filters_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDir::Filters value = qscriptvalue_cast<QDir::Filters>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDir_Filters_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDir::Filters value = qscriptvalue_cast<QDir::Filters>(context->thisObject());
    QString result;
    for (int i = 0; i < 20; ++i) {
        if ((value & qtscript_QDir_Filter_values[i]) == qtscript_QDir_Filter_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QDir_Filter_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QDir_Filters_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QDir::Filters>() == otherObj.value<QDir::Filters>())));
}

static QScriptValue qtscript_create_QDir_Filters_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QDir_Filters, qtscript_QDir_Filters_valueOf,
        qtscript_QDir_Filters_toString, qtscript_QDir_Filters_equals);
    qScriptRegisterMetaType<QDir::Filters>(engine, qtscript_QDir_Filters_toScriptValue,
        qtscript_QDir_Filters_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QDir
//

static QScriptValue qtscript_QDir_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 36;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDir* _q_self = qscriptvalue_cast<QDir*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDir.%0(): this object is not a QDir")
            .arg(qtscript_QDir_function_names[_id+22]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->absoluteFilePath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->absolutePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->canonicalPath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->cd(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->cdUp();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->dirName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QList<QFileInfo > _q_result = _q_self->entryInfoList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(0).toVariant().userType())) {
            QFlags<QDir::Filter> _q_arg0 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(0));
            QList<QFileInfo > _q_result = _q_self->entryInfoList(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if (context->argument(0).isArray()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QList<QFileInfo > _q_result = _q_self->entryInfoList(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QFlags<QDir::SortFlag> >() == context->argument(1).toVariant().userType())) {
            QFlags<QDir::Filter> _q_arg0 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(0));
            QFlags<QDir::SortFlag> _q_arg1 = qscriptvalue_cast<QFlags<QDir::SortFlag> >(context->argument(1));
            QList<QFileInfo > _q_result = _q_self->entryInfoList(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if (context->argument(0).isArray()
            && (qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(1).toVariant().userType())) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QFlags<QDir::Filter> _q_arg1 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(1));
            QList<QFileInfo > _q_result = _q_self->entryInfoList(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QFlags<QDir::Filter> _q_arg1 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(1));
        QFlags<QDir::SortFlag> _q_arg2 = qscriptvalue_cast<QFlags<QDir::SortFlag> >(context->argument(2));
        QList<QFileInfo > _q_result = _q_self->entryInfoList(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->entryList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(0).toVariant().userType())) {
            QFlags<QDir::Filter> _q_arg0 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(0));
            QStringList _q_result = _q_self->entryList(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if (context->argument(0).isArray()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QStringList _q_result = _q_self->entryList(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QFlags<QDir::SortFlag> >() == context->argument(1).toVariant().userType())) {
            QFlags<QDir::Filter> _q_arg0 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(0));
            QFlags<QDir::SortFlag> _q_arg1 = qscriptvalue_cast<QFlags<QDir::SortFlag> >(context->argument(1));
            QStringList _q_result = _q_self->entryList(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if (context->argument(0).isArray()
            && (qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(1).toVariant().userType())) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QFlags<QDir::Filter> _q_arg1 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(1));
            QStringList _q_result = _q_self->entryList(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QFlags<QDir::Filter> _q_arg1 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(1));
        QFlags<QDir::SortFlag> _q_arg2 = qscriptvalue_cast<QFlags<QDir::SortFlag> >(context->argument(2));
        QStringList _q_result = _q_self->entryList(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exists();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->exists(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->filePath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QFlags<QDir::Filter> _q_result = _q_self->filter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAbsolute();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isReadable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRelative();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRoot();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->makeAbsolute();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->mkdir(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->mkpath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->nameFilters();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->operator[](_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->path();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->refresh();
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->relativeFilePath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->remove(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->removeRecursively();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->rename(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->rmdir(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->rmpath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QFlags<QDir::Filter> _q_arg0 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(0));
        _q_self->setFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setNameFilters(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QFlags<QDir::SortFlag> _q_arg0 = qscriptvalue_cast<QFlags<QDir::SortFlag> >(context->argument(0));
        _q_self->setSorting(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        QFlags<QDir::SortFlag> _q_result = _q_self->sorting();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDir_throw_ambiguity_error_helper(context,
        qtscript_QDir_function_names[_id+22],
        qtscript_QDir_function_signatures[_id+22]);
}

static QScriptValue qtscript_QDir_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDir(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDir _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QDir>() == context->argument(0).toVariant().userType())) {
            QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
            QDir _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QDir _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDir _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QFlags<QDir::SortFlag> _q_arg2 = qscriptvalue_cast<QFlags<QDir::SortFlag> >(context->argument(2));
        QDir _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QFlags<QDir::SortFlag> _q_arg2 = qscriptvalue_cast<QFlags<QDir::SortFlag> >(context->argument(2));
        QFlags<QDir::Filter> _q_arg3 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(3));
        QDir _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDir::addSearchPath(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QDir::cleanPath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QDir _q_result = QDir::current();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = QDir::currentPath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QList<QFileInfo > _q_result = QDir::drives();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QDir::fromNativeSeparators(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QDir _q_result = QDir::home();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = QDir::homePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QDir::isAbsolutePath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QDir::isRelativePath(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            bool _q_result = QDir::match(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isArray()
            && context->argument(1).isString()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QString _q_arg1 = context->argument(1).toString();
            bool _q_result = QDir::match(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = QDir::nameFiltersFromString(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QDir _q_result = QDir::root();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QString _q_result = QDir::rootPath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = QDir::searchPaths(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QChar _q_result = QDir::separator();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QDir::setCurrent(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        QDir::setSearchPaths(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QDir _q_result = QDir::temp();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QString _q_result = QDir::tempPath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = QDir::toNativeSeparators(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDir_throw_ambiguity_error_helper(context,
        qtscript_QDir_function_names[_id],
        qtscript_QDir_function_signatures[_id]);
}

QScriptValue qtscript_create_QDir_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDir*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDir*)0));
    for (int i = 0; i < 37; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDir_prototype_call, qtscript_QDir_function_lengths[i+22]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDir_function_names[i+22]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDir>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDir*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDir_static_call, proto, qtscript_QDir_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDir_static_call,
            qtscript_QDir_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QDir_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("SortFlag"),
        qtscript_create_QDir_SortFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SortFlags"),
        qtscript_create_QDir_SortFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("Filter"),
        qtscript_create_QDir_Filter_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Filters"),
        qtscript_create_QDir_Filters_class(engine));
    return ctor;
}
