#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qurl.h>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qpair.h>
#include <qstringlist.h>
#include <qurl.h>

static const char * const qtscript_QUrl_function_names[] = {
    "QUrl"
    // static
    , "fromAce"
    , "fromEncoded"
    , "fromLocalFile"
    , "fromPercentEncoding"
    , "fromUserInput"
    , "idnWhitelist"
    , "setIdnWhitelist"
    , "toAce"
    , "toPercentEncoding"
    // prototype
    , "addEncodedQueryItem"
    , "addQueryItem"
    , "allEncodedQueryItemValues"
    , "allQueryItemValues"
    , "authority"
    , "clear"
    , "encodedFragment"
    , "encodedHost"
    , "encodedPassword"
    , "encodedPath"
    , "encodedQuery"
    , "encodedQueryItemValue"
    , "encodedQueryItems"
    , "encodedUserName"
    , "errorString"
    , "fragment"
    , "hasEncodedQueryItem"
    , "hasFragment"
    , "hasQuery"
    , "hasQueryItem"
    , "host"
    , "isEmpty"
    , "isLocalFile"
    , "isParentOf"
    , "isRelative"
    , "isValid"
    , "equals"
    , "operator_less"
    , "password"
    , "path"
    , "port"
    , "queryItemValue"
    , "queryItems"
    , "queryPairDelimiter"
    , "queryValueDelimiter"
    , "readFrom"
    , "removeAllEncodedQueryItems"
    , "removeAllQueryItems"
    , "removeEncodedQueryItem"
    , "removeQueryItem"
    , "resolved"
    , "scheme"
    , "setAuthority"
    , "setEncodedFragment"
    , "setEncodedHost"
    , "setEncodedPassword"
    , "setEncodedPath"
    , "setEncodedQuery"
    , "setEncodedQueryItems"
    , "setEncodedUrl"
    , "setEncodedUserName"
    , "setFragment"
    , "setHost"
    , "setPassword"
    , "setPath"
    , "setPort"
    , "setQueryDelimiters"
    , "setQueryItems"
    , "setScheme"
    , "setUrl"
    , "setUserInfo"
    , "setUserName"
    , "swap"
    , "toEncoded"
    , "toLocalFile"
    , "toString"
    , "topLevelDomain"
    , "userInfo"
    , "userName"
    , "writeTo"
};

static const char * const qtscript_QUrl_function_signatures[] = {
    "\nString url\nString url, ParsingMode mode\nQUrl copy"
    // static
    , "QByteArray arg__1"
    , "QByteArray url\nQByteArray url, ParsingMode mode"
    , "String localfile"
    , "QByteArray arg__1"
    , "String userInput"
    , ""
    , "List arg__1"
    , "String arg__1"
    , "String arg__1, QByteArray exclude, QByteArray include"
    // prototype
    , "QByteArray key, QByteArray value"
    , "String key, String value"
    , "QByteArray key"
    , "String key"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QByteArray key"
    , ""
    , ""
    , ""
    , ""
    , "QByteArray key"
    , ""
    , ""
    , "String key"
    , ""
    , ""
    , ""
    , "QUrl url"
    , ""
    , ""
    , "QUrl url"
    , "QUrl url"
    , ""
    , ""
    , "\nint defaultPort"
    , "String key"
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
    , "QByteArray key"
    , "String key"
    , "QByteArray key"
    , "String key"
    , "QUrl relative"
    , ""
    , "String authority"
    , "QByteArray fragment"
    , "QByteArray host"
    , "QByteArray password"
    , "QByteArray path"
    , "QByteArray query"
    , "List query"
    , "QByteArray url\nQByteArray url, ParsingMode mode"
    , "QByteArray userName"
    , "String fragment"
    , "String host"
    , "String password"
    , "String path"
    , "int port"
    , "char valueDelimiter, char pairDelimiter"
    , "List query"
    , "String scheme"
    , "String url\nString url, ParsingMode mode"
    , "String userInfo"
    , "String userName"
    , "QUrl other"
    , "FormattingOptions options"
    , ""
    , "FormattingOptions options"
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
};

static const int qtscript_QUrl_function_lengths[] = {
    2
    // static
    , 1
    , 2
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 3
    // prototype
    , 2
    , 2
    , 1
    , 1
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
    , 0
    , 1
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
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
    , 1
};

static QScriptValue qtscript_QUrl_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUrl::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUrl*)
Q_DECLARE_METATYPE(QUrl::ParsingMode)
Q_DECLARE_METATYPE(QUrl::FormattingOption)
Q_DECLARE_METATYPE(QFlags<QUrl::FormattingOption>)
Q_DECLARE_METATYPE(QList<QByteArray>)
template <> \
struct QMetaTypeId< QPair<QByteArray,QByteArray> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<QByteArray,QByteArray> >("QPair<QByteArray,QByteArray>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<QByteArray,QByteArray> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QList<QPair<QByteArray,QByteArray> > >("QList<QPair<QByteArray,QByteArray> >"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QPair<QString,QString> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<QString,QString> >("QPair<QString,QString>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<QString,QString> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QList<QPair<QString,QString> > >("QList<QPair<QString,QString> >"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(QDataStream*)

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
// QUrl::ParsingMode
//

static const QUrl::ParsingMode qtscript_QUrl_ParsingMode_values[] = {
    QUrl::TolerantMode
    , QUrl::StrictMode
};

static const char * const qtscript_QUrl_ParsingMode_keys[] = {
    "TolerantMode"
    , "StrictMode"
};

static QString qtscript_QUrl_ParsingMode_toStringHelper(QUrl::ParsingMode value)
{
    if ((value >= QUrl::TolerantMode) && (value <= QUrl::StrictMode))
        return qtscript_QUrl_ParsingMode_keys[static_cast<int>(value)-static_cast<int>(QUrl::TolerantMode)];
    return QString();
}

static QScriptValue qtscript_QUrl_ParsingMode_toScriptValue(QScriptEngine *engine, const QUrl::ParsingMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QUrl"));
    return clazz.property(qtscript_QUrl_ParsingMode_toStringHelper(value));
}

static void qtscript_QUrl_ParsingMode_fromScriptValue(const QScriptValue &value, QUrl::ParsingMode &out)
{
    out = qvariant_cast<QUrl::ParsingMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QUrl_ParsingMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QUrl::TolerantMode) && (arg <= QUrl::StrictMode))
        return qScriptValueFromValue(engine,  static_cast<QUrl::ParsingMode>(arg));
    return context->throwError(QString::fromLatin1("ParsingMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QUrl_ParsingMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUrl::ParsingMode value = qscriptvalue_cast<QUrl::ParsingMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUrl_ParsingMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUrl::ParsingMode value = qscriptvalue_cast<QUrl::ParsingMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QUrl_ParsingMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QUrl_ParsingMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QUrl_ParsingMode,
        qtscript_QUrl_ParsingMode_valueOf, qtscript_QUrl_ParsingMode_toString);
    qScriptRegisterMetaType<QUrl::ParsingMode>(engine, qtscript_QUrl_ParsingMode_toScriptValue,
        qtscript_QUrl_ParsingMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QUrl_ParsingMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QUrl_ParsingMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QUrl::FormattingOption
//

static const QUrl::FormattingOption qtscript_QUrl_FormattingOption_values[] = {
    QUrl::None
    , QUrl::RemoveScheme
    , QUrl::RemovePassword
    , QUrl::RemoveUserInfo
    , QUrl::RemovePort
    , QUrl::RemoveAuthority
    , QUrl::RemovePath
    , QUrl::RemoveQuery
    , QUrl::RemoveFragment
    , QUrl::StripTrailingSlash
};

static const char * const qtscript_QUrl_FormattingOption_keys[] = {
    "None"
    , "RemoveScheme"
    , "RemovePassword"
    , "RemoveUserInfo"
    , "RemovePort"
    , "RemoveAuthority"
    , "RemovePath"
    , "RemoveQuery"
    , "RemoveFragment"
    , "StripTrailingSlash"
};

static QString qtscript_QUrl_FormattingOption_toStringHelper(QUrl::FormattingOption value)
{
    for (int i = 0; i < 10; ++i) {
        if (qtscript_QUrl_FormattingOption_values[i] == value)
            return QString::fromLatin1(qtscript_QUrl_FormattingOption_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QUrl_FormattingOption_toScriptValue(QScriptEngine *engine, const QUrl::FormattingOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QUrl"));
    return clazz.property(qtscript_QUrl_FormattingOption_toStringHelper(value));
}

static void qtscript_QUrl_FormattingOption_fromScriptValue(const QScriptValue &value, QUrl::FormattingOption &out)
{
    out = qvariant_cast<QUrl::FormattingOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QUrl_FormattingOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 10; ++i) {
        if (qtscript_QUrl_FormattingOption_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QUrl::FormattingOption>(arg));
    }
    return context->throwError(QString::fromLatin1("FormattingOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QUrl_FormattingOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUrl::FormattingOption value = qscriptvalue_cast<QUrl::FormattingOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUrl_FormattingOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUrl::FormattingOption value = qscriptvalue_cast<QUrl::FormattingOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QUrl_FormattingOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QUrl_FormattingOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QUrl_FormattingOption,
        qtscript_QUrl_FormattingOption_valueOf, qtscript_QUrl_FormattingOption_toString);
    qScriptRegisterMetaType<QUrl::FormattingOption>(engine, qtscript_QUrl_FormattingOption_toScriptValue,
        qtscript_QUrl_FormattingOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 10; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QUrl_FormattingOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QUrl_FormattingOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QUrl::FormattingOptions
//

static QScriptValue qtscript_QUrl_FormattingOptions_toScriptValue(QScriptEngine *engine, const QUrl::FormattingOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QUrl_FormattingOptions_fromScriptValue(const QScriptValue &value, QUrl::FormattingOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QUrl::FormattingOptions>())
        out = qvariant_cast<QUrl::FormattingOptions>(var);
    else if (var.userType() == qMetaTypeId<QUrl::FormattingOption>())
        out = qvariant_cast<QUrl::FormattingOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QUrl_FormattingOptions(QScriptContext *context, QScriptEngine *engine)
{
    QUrl::FormattingOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QUrl::FormattingOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QUrl::FormattingOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("FormattingOptions(): argument %0 is not of type FormattingOption").arg(i));
            }
            result |= qvariant_cast<QUrl::FormattingOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QUrl_FormattingOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QUrl::FormattingOptions value = qscriptvalue_cast<QUrl::FormattingOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QUrl_FormattingOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QUrl::FormattingOptions value = qscriptvalue_cast<QUrl::FormattingOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 10; ++i) {
        if ((value & qtscript_QUrl_FormattingOption_values[i]) == qtscript_QUrl_FormattingOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QUrl_FormattingOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QUrl_FormattingOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QUrl::FormattingOptions>() == otherObj.value<QUrl::FormattingOptions>())));
}

static QScriptValue qtscript_create_QUrl_FormattingOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QUrl_FormattingOptions, qtscript_QUrl_FormattingOptions_valueOf,
        qtscript_QUrl_FormattingOptions_toString, qtscript_QUrl_FormattingOptions_equals);
    qScriptRegisterMetaType<QUrl::FormattingOptions>(engine, qtscript_QUrl_FormattingOptions_toScriptValue,
        qtscript_QUrl_FormattingOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QUrl
//

static QScriptValue qtscript_QUrl_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 70;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUrl* _q_self = qscriptvalue_cast<QUrl*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUrl.%0(): this object is not a QUrl")
            .arg(qtscript_QUrl_function_names[_id+10]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        _q_self->addEncodedQueryItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->addQueryItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QList<QByteArray> _q_result = _q_self->allEncodedQueryItemValues(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = _q_self->allQueryItemValues(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->authority();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->encodedFragment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->encodedHost();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->encodedPassword();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->encodedPath();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->encodedQuery();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = _q_self->encodedQueryItemValue(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QList<QPair<QByteArray,QByteArray> > _q_result = _q_self->encodedQueryItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->encodedUserName();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fragment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->hasEncodedQueryItem(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasFragment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasQuery();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasQueryItem(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->host();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLocalFile();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = _q_self->isParentOf(_q_arg0);
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
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->password();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->path();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->port();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->port(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->queryItemValue(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QList<QPair<QString,QString> > _q_result = _q_self->queryItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        char _q_result = _q_self->queryPairDelimiter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        char _q_result = _q_self->queryValueDelimiter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->removeAllEncodedQueryItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeAllQueryItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->removeEncodedQueryItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeQueryItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        QUrl _q_result = _q_self->resolved(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->scheme();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setAuthority(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setEncodedFragment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setEncodedHost(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setEncodedPassword(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setEncodedPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setEncodedQuery(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 1) {
        QList<QPair<QByteArray,QByteArray> > _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setEncodedQueryItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setEncodedUrl(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setEncodedUrl(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setEncodedUserName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 51:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFragment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHost(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPassword(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 56:
    if (context->argumentCount() == 2) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        char _q_arg1 = qscriptvalue_cast<char>(context->argument(1));
        _q_self->setQueryDelimiters(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 1) {
        QList<QPair<QString,QString> > _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setQueryItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 58:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setScheme(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 59:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setUrl(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setUrl(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 60:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setUserInfo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 61:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setUserName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 62:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 63:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toEncoded();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<QUrl::FormattingOption> _q_arg0 = qscriptvalue_cast<QFlags<QUrl::FormattingOption> >(context->argument(0));
        QByteArray _q_result = _q_self->toEncoded(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 64:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toLocalFile();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 65:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<QUrl::FormattingOption> _q_arg0 = qscriptvalue_cast<QFlags<QUrl::FormattingOption> >(context->argument(0));
        QString _q_result = _q_self->toString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 66:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->topLevelDomain();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 67:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->userInfo();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 68:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->userName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 69:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUrl_throw_ambiguity_error_helper(context,
        qtscript_QUrl_function_names[_id+10],
        qtscript_QUrl_function_signatures[_id+10]);
}

static QScriptValue qtscript_QUrl_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUrl(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QUrl _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QUrl _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            QUrl _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        QUrl _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_result = QUrl::fromAce(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QUrl _q_result = QUrl::fromEncoded(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        QUrl _q_result = QUrl::fromEncoded(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl _q_result = QUrl::fromLocalFile(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_result = QUrl::fromPercentEncoding(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl _q_result = QUrl::fromUserInput(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QUrl::idnWhitelist();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QUrl::setIdnWhitelist(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = QUrl::toAce(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = QUrl::toPercentEncoding(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QByteArray _q_result = QUrl::toPercentEncoding(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        QByteArray _q_arg2 = qscriptvalue_cast<QByteArray>(context->argument(2));
        QByteArray _q_result = QUrl::toPercentEncoding(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUrl_throw_ambiguity_error_helper(context,
        qtscript_QUrl_function_names[_id],
        qtscript_QUrl_function_signatures[_id]);
}

QScriptValue qtscript_create_QUrl_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUrl*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUrl*)0));
    for (int i = 0; i < 70; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUrl_prototype_call, qtscript_QUrl_function_lengths[i+10]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUrl_function_names[i+10]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QUrl>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QUrl*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUrl_static_call, proto, qtscript_QUrl_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUrl_static_call,
            qtscript_QUrl_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QUrl_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ParsingMode"),
        qtscript_create_QUrl_ParsingMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FormattingOption"),
        qtscript_create_QUrl_FormattingOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FormattingOptions"),
        qtscript_create_QUrl_FormattingOptions_class(engine));
    return ctor;
}
