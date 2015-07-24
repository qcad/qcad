#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsslcertificate.h>
#include <QDateTime>
#include <QVariant>
#include <qbytearray.h>
#include <qdatetime.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qsslcertificate.h>
#include <qsslerror.h>
#include <qsslkey.h>
#include <qstringlist.h>

static const char * const qtscript_QSslCertificate_function_names[] = {
    "QSslCertificate"
    // static
    , "fromData"
    , "fromDevice"
    , "fromPath"
    , "verify"
    // prototype
    , "clear"
    , "digest"
    , "effectiveDate"
    , "expiryDate"
    , "handle"
    , "isBlacklisted"
    , "isNull"
    , "issuerInfo"
    , "issuerInfoAttributes"
    , "operator_assign"
    , "equals"
    , "publicKey"
    , "serialNumber"
    , "subjectInfo"
    , "subjectInfoAttributes"
    , "swap"
    , "toDer"
    , "toPem"
    , "toText"
    , "version"
    , "toString"
};

static const char * const qtscript_QSslCertificate_function_signatures[] = {
    "QIODevice device, EncodingFormat format\nQByteArray data, EncodingFormat format\nQSslCertificate other"
    // static
    , "QByteArray data, EncodingFormat format"
    , "QIODevice device, EncodingFormat format"
    , "String path, EncodingFormat format, PatternSyntax syntax"
    , "List certificateChain, String hostName"
    // prototype
    , ""
    , "Algorithm algorithm"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "SubjectInfo info\nQByteArray attribute"
    , ""
    , "QSslCertificate other"
    , "QSslCertificate other"
    , ""
    , ""
    , "SubjectInfo info\nQByteArray attribute"
    , ""
    , "QSslCertificate other"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QSslCertificate_function_lengths[] = {
    2
    // static
    , 2
    , 2
    , 3
    , 2
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSslCertificate_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSslCertificate::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSslCertificate*)
Q_DECLARE_METATYPE(QSslCertificate::SubjectInfo)
Q_DECLARE_METATYPE(QCryptographicHash::Algorithm)
Q_DECLARE_METATYPE(Qt::HANDLE)
Q_DECLARE_METATYPE(QList<QByteArray >)
Q_DECLARE_METATYPE(QSslKey)
Q_DECLARE_METATYPE(QSsl::EncodingFormat)
Q_DECLARE_METATYPE(QList<QSslCertificate >)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QRegExp::PatternSyntax)
Q_DECLARE_METATYPE(QSslError)

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
// QSslCertificate::SubjectInfo
//

static const QSslCertificate::SubjectInfo qtscript_QSslCertificate_SubjectInfo_values[] = {
    QSslCertificate::Organization
    , QSslCertificate::CommonName
    , QSslCertificate::LocalityName
    , QSslCertificate::OrganizationalUnitName
    , QSslCertificate::CountryName
    , QSslCertificate::StateOrProvinceName
    , QSslCertificate::DistinguishedNameQualifier
    , QSslCertificate::SerialNumber
    , QSslCertificate::EmailAddress
};

static const char * const qtscript_QSslCertificate_SubjectInfo_keys[] = {
    "Organization"
    , "CommonName"
    , "LocalityName"
    , "OrganizationalUnitName"
    , "CountryName"
    , "StateOrProvinceName"
    , "DistinguishedNameQualifier"
    , "SerialNumber"
    , "EmailAddress"
};

static QString qtscript_QSslCertificate_SubjectInfo_toStringHelper(QSslCertificate::SubjectInfo value)
{
    if ((value >= QSslCertificate::Organization) && (value <= QSslCertificate::EmailAddress))
        return qtscript_QSslCertificate_SubjectInfo_keys[static_cast<int>(value)-static_cast<int>(QSslCertificate::Organization)];
    return QString();
}

static QScriptValue qtscript_QSslCertificate_SubjectInfo_toScriptValue(QScriptEngine *engine, const QSslCertificate::SubjectInfo &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSslCertificate"));
    return clazz.property(qtscript_QSslCertificate_SubjectInfo_toStringHelper(value));
}

static void qtscript_QSslCertificate_SubjectInfo_fromScriptValue(const QScriptValue &value, QSslCertificate::SubjectInfo &out)
{
    out = qvariant_cast<QSslCertificate::SubjectInfo>(value.toVariant());
}

static QScriptValue qtscript_construct_QSslCertificate_SubjectInfo(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSslCertificate::Organization) && (arg <= QSslCertificate::EmailAddress))
        return qScriptValueFromValue(engine,  static_cast<QSslCertificate::SubjectInfo>(arg));
    return context->throwError(QString::fromLatin1("SubjectInfo(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSslCertificate_SubjectInfo_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSslCertificate::SubjectInfo value = qscriptvalue_cast<QSslCertificate::SubjectInfo>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSslCertificate_SubjectInfo_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSslCertificate::SubjectInfo value = qscriptvalue_cast<QSslCertificate::SubjectInfo>(context->thisObject());
    return QScriptValue(engine, qtscript_QSslCertificate_SubjectInfo_toStringHelper(value));
}

static QScriptValue qtscript_create_QSslCertificate_SubjectInfo_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSslCertificate_SubjectInfo,
        qtscript_QSslCertificate_SubjectInfo_valueOf, qtscript_QSslCertificate_SubjectInfo_toString);
    qScriptRegisterMetaType<QSslCertificate::SubjectInfo>(engine, qtscript_QSslCertificate_SubjectInfo_toScriptValue,
        qtscript_QSslCertificate_SubjectInfo_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 9; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSslCertificate_SubjectInfo_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSslCertificate_SubjectInfo_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSslCertificate
//

static QScriptValue qtscript_QSslCertificate_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSslCertificate* _q_self = qscriptvalue_cast<QSslCertificate*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSslCertificate.%0(): this object is not a QSslCertificate")
            .arg(qtscript_QSslCertificate_function_names[_id+5]));
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
        QByteArray _q_result = _q_self->digest();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QCryptographicHash::Algorithm _q_arg0 = qscriptvalue_cast<QCryptographicHash::Algorithm>(context->argument(0));
        QByteArray _q_result = _q_self->digest(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->effectiveDate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QDateTime _q_result = _q_self->expiryDate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        Qt::HANDLE _q_result = _q_self->handle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isBlacklisted();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSslCertificate::SubjectInfo>() == context->argument(0).toVariant().userType())) {
            QSslCertificate::SubjectInfo _q_arg0 = qscriptvalue_cast<QSslCertificate::SubjectInfo>(context->argument(0));
            QStringList _q_result = _q_self->issuerInfo(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QStringList _q_result = _q_self->issuerInfo(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = _q_self->issuerInfoAttributes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
        QSslCertificate& _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QSslKey _q_result = _q_self->publicKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->serialNumber();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSslCertificate::SubjectInfo>() == context->argument(0).toVariant().userType())) {
            QSslCertificate::SubjectInfo _q_arg0 = qscriptvalue_cast<QSslCertificate::SubjectInfo>(context->argument(0));
            QStringList _q_result = _q_self->subjectInfo(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QStringList _q_result = _q_self->subjectInfo(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = _q_self->subjectInfoAttributes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toDer();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->toPem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->version();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslCertificate_throw_ambiguity_error_helper(context,
        qtscript_QSslCertificate_function_names[_id+5],
        qtscript_QSslCertificate_function_signatures[_id+5]);
}

static QScriptValue qtscript_QSslCertificate_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSslCertificate(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSslCertificate _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QSslCertificate _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QSslCertificate _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QSslCertificate>() == context->argument(0).toVariant().userType())) {
            QSslCertificate _q_arg0 = qscriptvalue_cast<QSslCertificate>(context->argument(0));
            QSslCertificate _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
            QSslCertificate _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSsl::EncodingFormat>() == context->argument(1).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
            QSslCertificate _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QList<QSslCertificate > _q_result = QSslCertificate::fromData(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        QList<QSslCertificate > _q_result = QSslCertificate::fromData(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QList<QSslCertificate > _q_result = QSslCertificate::fromDevice(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        QList<QSslCertificate > _q_result = QSslCertificate::fromDevice(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QList<QSslCertificate > _q_result = QSslCertificate::fromPath(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        QList<QSslCertificate > _q_result = QSslCertificate::fromPath(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QSsl::EncodingFormat _q_arg1 = qscriptvalue_cast<QSsl::EncodingFormat>(context->argument(1));
        QRegExp::PatternSyntax _q_arg2 = qscriptvalue_cast<QRegExp::PatternSyntax>(context->argument(2));
        QList<QSslCertificate > _q_result = QSslCertificate::fromPath(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QList<QSslCertificate> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QList<QSslError > _q_result = QSslCertificate::verify(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QList<QSslCertificate> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QString _q_arg1 = context->argument(1).toString();
        QList<QSslError > _q_result = QSslCertificate::verify(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSslCertificate_throw_ambiguity_error_helper(context,
        qtscript_QSslCertificate_function_names[_id],
        qtscript_QSslCertificate_function_signatures[_id]);
}

QScriptValue qtscript_create_QSslCertificate_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSslCertificate*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSslCertificate*)0));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslCertificate_prototype_call, qtscript_QSslCertificate_function_lengths[i+5]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSslCertificate_function_names[i+5]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSslCertificate>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSslCertificate*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSslCertificate_static_call, proto, qtscript_QSslCertificate_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSslCertificate_static_call,
            qtscript_QSslCertificate_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSslCertificate_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("SubjectInfo"),
        qtscript_create_QSslCertificate_SubjectInfo_class(engine, ctor));
    return ctor;
}
