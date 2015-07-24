#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlibraryinfo.h>
#include <QVariant>
#include <qdatetime.h>
#include <qstringlist.h>

static const char * const qtscript_QLibraryInfo_function_names[] = {
    "QLibraryInfo"
    // static
    , "build"
    , "buildDate"
    , "isDebugBuild"
    , "licensedProducts"
    , "licensee"
    , "location"
    , "platformPluginArguments"
    // prototype
    , "toString"
};

static const char * const qtscript_QLibraryInfo_function_signatures[] = {
    ""
    // static
    , ""
    , ""
    , ""
    , ""
    , ""
    , "LibraryLocation arg__1"
    , "String platformName"
    // prototype
""
};

static const int qtscript_QLibraryInfo_function_lengths[] = {
    0
    // static
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    // prototype
    , 0
};

static QScriptValue qtscript_QLibraryInfo_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLibraryInfo::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QLibraryInfo*)
Q_DECLARE_METATYPE(QLibraryInfo::LibraryLocation)
Q_DECLARE_METATYPE(const char*)

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

//
// QLibraryInfo::LibraryLocation
//

static const QLibraryInfo::LibraryLocation qtscript_QLibraryInfo_LibraryLocation_values[] = {
    QLibraryInfo::PrefixPath
    , QLibraryInfo::DocumentationPath
    , QLibraryInfo::HeadersPath
    , QLibraryInfo::LibrariesPath
    , QLibraryInfo::LibraryExecutablesPath
    , QLibraryInfo::BinariesPath
    , QLibraryInfo::PluginsPath
    , QLibraryInfo::ImportsPath
    , QLibraryInfo::Qml2ImportsPath
    , QLibraryInfo::ArchDataPath
    , QLibraryInfo::DataPath
    , QLibraryInfo::TranslationsPath
    , QLibraryInfo::ExamplesPath
    , QLibraryInfo::TestsPath
    , QLibraryInfo::SettingsPath
};

static const char * const qtscript_QLibraryInfo_LibraryLocation_keys[] = {
    "PrefixPath"
    , "DocumentationPath"
    , "HeadersPath"
    , "LibrariesPath"
    , "LibraryExecutablesPath"
    , "BinariesPath"
    , "PluginsPath"
    , "ImportsPath"
    , "Qml2ImportsPath"
    , "ArchDataPath"
    , "DataPath"
    , "TranslationsPath"
    , "ExamplesPath"
    , "TestsPath"
    , "SettingsPath"
};

static QString qtscript_QLibraryInfo_LibraryLocation_toStringHelper(QLibraryInfo::LibraryLocation value)
{
    for (int i = 0; i < 15; ++i) {
        if (qtscript_QLibraryInfo_LibraryLocation_values[i] == value)
            return QString::fromLatin1(qtscript_QLibraryInfo_LibraryLocation_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QLibraryInfo_LibraryLocation_toScriptValue(QScriptEngine *engine, const QLibraryInfo::LibraryLocation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLibraryInfo"));
    return clazz.property(qtscript_QLibraryInfo_LibraryLocation_toStringHelper(value));
}

static void qtscript_QLibraryInfo_LibraryLocation_fromScriptValue(const QScriptValue &value, QLibraryInfo::LibraryLocation &out)
{
    out = qvariant_cast<QLibraryInfo::LibraryLocation>(value.toVariant());
}

static QScriptValue qtscript_construct_QLibraryInfo_LibraryLocation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 15; ++i) {
        if (qtscript_QLibraryInfo_LibraryLocation_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QLibraryInfo::LibraryLocation>(arg));
    }
    return context->throwError(QString::fromLatin1("LibraryLocation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLibraryInfo_LibraryLocation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLibraryInfo::LibraryLocation value = qscriptvalue_cast<QLibraryInfo::LibraryLocation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLibraryInfo_LibraryLocation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLibraryInfo::LibraryLocation value = qscriptvalue_cast<QLibraryInfo::LibraryLocation>(context->thisObject());
    return QScriptValue(engine, qtscript_QLibraryInfo_LibraryLocation_toStringHelper(value));
}

static QScriptValue qtscript_create_QLibraryInfo_LibraryLocation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLibraryInfo_LibraryLocation,
        qtscript_QLibraryInfo_LibraryLocation_valueOf, qtscript_QLibraryInfo_LibraryLocation_toString);
    qScriptRegisterMetaType<QLibraryInfo::LibraryLocation>(engine, qtscript_QLibraryInfo_LibraryLocation_toScriptValue,
        qtscript_QLibraryInfo_LibraryLocation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLibraryInfo_LibraryLocation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLibraryInfo_LibraryLocation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLibraryInfo
//

static QScriptValue qtscript_QLibraryInfo_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QLibraryInfo* _q_self = qscriptvalue_cast<QLibraryInfo*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLibraryInfo.%0(): this object is not a QLibraryInfo")
            .arg(qtscript_QLibraryInfo_function_names[_id+8]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QLibraryInfo");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLibraryInfo_throw_ambiguity_error_helper(context,
        qtscript_QLibraryInfo_function_names[_id+8],
        qtscript_QLibraryInfo_function_signatures[_id+8]);
}

static QScriptValue qtscript_QLibraryInfo_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QLibraryInfo cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        const char* _q_result = const_cast<const char*>(QLibraryInfo::build());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QDate _q_result = QLibraryInfo::buildDate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = QLibraryInfo::isDebugBuild();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = QLibraryInfo::licensedProducts();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = QLibraryInfo::licensee();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QLibraryInfo::LibraryLocation _q_arg0 = qscriptvalue_cast<QLibraryInfo::LibraryLocation>(context->argument(0));
        QString _q_result = QLibraryInfo::location(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = QLibraryInfo::platformPluginArguments(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLibraryInfo_throw_ambiguity_error_helper(context,
        qtscript_QLibraryInfo_function_names[_id],
        qtscript_QLibraryInfo_function_signatures[_id]);
}

QScriptValue qtscript_create_QLibraryInfo_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLibraryInfo*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLibraryInfo*)0));

    engine->setDefaultPrototype(qMetaTypeId<QLibraryInfo*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLibraryInfo_static_call, proto, qtscript_QLibraryInfo_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLibraryInfo_static_call,
            qtscript_QLibraryInfo_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QLibraryInfo_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("LibraryLocation"),
        qtscript_create_QLibraryInfo_LibraryLocation_class(engine, ctor));
    return ctor;
}
