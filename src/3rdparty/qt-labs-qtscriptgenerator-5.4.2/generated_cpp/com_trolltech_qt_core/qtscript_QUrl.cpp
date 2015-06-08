#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qurl.h>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qlist.h>
#include <qstringlist.h>
#include <qurl.h>

static const char * const qtscript_QUrl_function_names[] = {
    "QUrl"
    // static
    , "fromAce"
    , "fromEncoded"
    , "fromLocalFile"
    , "fromPercentEncoding"
    , "fromStringList"
    , "fromUserInput"
    , "idnWhitelist"
    , "setIdnWhitelist"
    , "toAce"
    , "toPercentEncoding"
    // prototype
    , "clear"
    , "errorString"
    , "hasFragment"
    , "hasQuery"
    , "isEmpty"
    , "isLocalFile"
    , "isParentOf"
    , "isRelative"
    , "isValid"
    , "equals"
    , "operator_less"
    , "port"
    , "resolved"
    , "scheme"
    , "setAuthority"
    , "setFragment"
    , "setHost"
    , "setPassword"
    , "setPath"
    , "setPort"
    , "setQuery"
    , "setScheme"
    , "setUrl"
    , "setUserInfo"
    , "setUserName"
    , "swap"
    , "toLocalFile"
    , "toString"
    , "path"
    , "fragment"
};

static const char * const qtscript_QUrl_function_signatures[] = {
    "\nString url, ParsingMode mode\nQUrl copy"
    // static
    , "QByteArray arg__1"
    , "QByteArray url, ParsingMode mode"
    , "String localfile"
    , "QByteArray arg__1"
    , "List uris, ParsingMode mode"
    , "String userInput"
    , ""
    , "List arg__1"
    , "String arg__1"
    , "String arg__1, QByteArray exclude, QByteArray include"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QUrl url"
    , ""
    , ""
    , "QUrl url"
    , "QUrl url"
    , "int defaultPort"
    , "QUrl relative"
    , ""
    , "String authority, ParsingMode mode"
    , "String fragment, ParsingMode mode"
    , "String host, ParsingMode mode"
    , "String password, ParsingMode mode"
    , "String path, ParsingMode mode"
    , "int port"
    , "String query, ParsingMode mode"
    , "String scheme"
    , "String url, ParsingMode mode"
    , "String userInfo, ParsingMode mode"
    , "String userName, ParsingMode mode"
    , "QUrl other"
    , ""
    , ""
    , ""
    , ""
};

static const int qtscript_QUrl_function_lengths[] = {
    2
    // static
    , 1
    , 2
    , 1
    , 1
    , 2
    , 1
    , 0
    , 1
    , 1
    , 3
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 2
    , 2
    , 2
    , 2
    , 2
    , 1
    , 2
    , 1
    , 2
    , 2
    , 2
    , 1
    , 0
    , 0
    , 0
    , 0
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
Q_DECLARE_METATYPE(QList<QUrl >)

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
// QUrl::ParsingMode
//

static const QUrl::ParsingMode qtscript_QUrl_ParsingMode_values[] = {
    QUrl::TolerantMode
    , QUrl::StrictMode
    , QUrl::DecodedMode
};

static const char * const qtscript_QUrl_ParsingMode_keys[] = {
    "TolerantMode"
    , "StrictMode"
    , "DecodedMode"
};

static QString qtscript_QUrl_ParsingMode_toStringHelper(QUrl::ParsingMode value)
{
    if ((value >= QUrl::TolerantMode) && (value <= QUrl::DecodedMode))
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
    if ((arg >= QUrl::TolerantMode) && (arg <= QUrl::DecodedMode))
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
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QUrl_ParsingMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QUrl_ParsingMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
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
        _id = 0xBABE0000 + 29;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUrl* _q_self = qscriptvalue_cast<QUrl*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUrl.%0(): this object is not a QUrl")
            .arg(qtscript_QUrl_function_names[_id+11]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->errorString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasFragment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasQuery();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLocalFile();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = _q_self->isParentOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRelative();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
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

    case 12:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        QUrl _q_result = _q_self->resolved(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->scheme();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setAuthority(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setAuthority(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFragment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setFragment(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHost(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setHost(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPassword(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setPassword(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setPath(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setQuery(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setQuery(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setScheme(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
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

    case 23:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setUserInfo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setUserInfo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setUserName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        _q_self->setUserName(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toLocalFile();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->path();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fragment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUrl_throw_ambiguity_error_helper(context,
        qtscript_QUrl_function_names[_id+11],
        qtscript_QUrl_function_signatures[_id+11]);
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
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QList<QUrl > _q_result = QUrl::fromStringList(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QUrl::ParsingMode _q_arg1 = qscriptvalue_cast<QUrl::ParsingMode>(context->argument(1));
        QList<QUrl > _q_result = QUrl::fromStringList(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl _q_result = QUrl::fromUserInput(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QUrl::idnWhitelist();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QUrl::setIdnWhitelist(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = QUrl::toAce(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
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
    for (int i = 0; i < 30; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUrl_prototype_call, qtscript_QUrl_function_lengths[i+11]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUrl_function_names[i+11]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QUrl>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QUrl*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUrl_static_call, proto, qtscript_QUrl_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUrl_static_call,
            qtscript_QUrl_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QUrl_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ParsingMode"),
        qtscript_create_QUrl_ParsingMode_class(engine, ctor));
    return ctor;
}
