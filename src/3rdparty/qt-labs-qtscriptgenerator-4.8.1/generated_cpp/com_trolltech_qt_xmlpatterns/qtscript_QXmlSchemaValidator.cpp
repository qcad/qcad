#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlschemavalidator.h>
#include <QVariant>
#include <qabstractmessagehandler.h>
#include <qabstracturiresolver.h>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qnetworkaccessmanager.h>
#include <qurl.h>
#include <qxmlnamepool.h>
#include <qxmlschema.h>
#include <qxmlschemavalidator.h>

static const char * const qtscript_QXmlSchemaValidator_function_names[] = {
    "QXmlSchemaValidator"
    // static
    // prototype
    , "messageHandler"
    , "namePool"
    , "networkAccessManager"
    , "schema"
    , "setMessageHandler"
    , "setNetworkAccessManager"
    , "setSchema"
    , "setUriResolver"
    , "uriResolver"
    , "validate"
    , "toString"
};

static const char * const qtscript_QXmlSchemaValidator_function_signatures[] = {
    "\nQXmlSchema schema"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QAbstractMessageHandler handler"
    , "QNetworkAccessManager networkmanager"
    , "QXmlSchema schema"
    , "QAbstractUriResolver resolver"
    , ""
    , "QIODevice source, QUrl documentUri\nQByteArray data, QUrl documentUri\nQUrl source"
""
};

static const int qtscript_QXmlSchemaValidator_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_QXmlSchemaValidator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlSchemaValidator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlSchemaValidator*)
Q_DECLARE_METATYPE(QAbstractMessageHandler*)
Q_DECLARE_METATYPE(QXmlNamePool)
Q_DECLARE_METATYPE(QNetworkAccessManager*)
Q_DECLARE_METATYPE(QXmlSchema)
Q_DECLARE_METATYPE(QAbstractUriResolver*)
Q_DECLARE_METATYPE(QIODevice*)

//
// QXmlSchemaValidator
//

static QScriptValue qtscript_QXmlSchemaValidator_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlSchemaValidator* _q_self = qscriptvalue_cast<QXmlSchemaValidator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlSchemaValidator.%0(): this object is not a QXmlSchemaValidator")
            .arg(qtscript_QXmlSchemaValidator_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QAbstractMessageHandler* _q_result = _q_self->messageHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QXmlNamePool _q_result = _q_self->namePool();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QNetworkAccessManager* _q_result = _q_self->networkAccessManager();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QXmlSchema _q_result = _q_self->schema();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QAbstractMessageHandler* _q_arg0 = qscriptvalue_cast<QAbstractMessageHandler*>(context->argument(0));
        _q_self->setMessageHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QNetworkAccessManager* _q_arg0 = qscriptvalue_cast<QNetworkAccessManager*>(context->argument(0));
        _q_self->setNetworkAccessManager(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QXmlSchema _q_arg0 = qscriptvalue_cast<QXmlSchema>(context->argument(0));
        _q_self->setSchema(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QAbstractUriResolver* _q_arg0 = qscriptvalue_cast<QAbstractUriResolver*>(context->argument(0));
        _q_self->setUriResolver(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QAbstractUriResolver* _q_result = const_cast<QAbstractUriResolver*>(_q_self->uriResolver());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_result = _q_self->validate(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            bool _q_result = _q_self->validate(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            bool _q_result = _q_self->validate(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QUrl>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
            bool _q_result = _q_self->validate(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QUrl>() == context->argument(1).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
            bool _q_result = _q_self->validate(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QXmlSchemaValidator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlSchemaValidator_throw_ambiguity_error_helper(context,
        qtscript_QXmlSchemaValidator_function_names[_id+1],
        qtscript_QXmlSchemaValidator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlSchemaValidator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlSchemaValidator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlSchemaValidator* _q_cpp_result = new QXmlSchemaValidator();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QXmlSchema _q_arg0 = qscriptvalue_cast<QXmlSchema>(context->argument(0));
        QXmlSchemaValidator* _q_cpp_result = new QXmlSchemaValidator(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlSchemaValidator_throw_ambiguity_error_helper(context,
        qtscript_QXmlSchemaValidator_function_names[_id],
        qtscript_QXmlSchemaValidator_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlSchemaValidator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlSchemaValidator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlSchemaValidator*)0));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlSchemaValidator_prototype_call, qtscript_QXmlSchemaValidator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlSchemaValidator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlSchemaValidator*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlSchemaValidator_static_call, proto, qtscript_QXmlSchemaValidator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
