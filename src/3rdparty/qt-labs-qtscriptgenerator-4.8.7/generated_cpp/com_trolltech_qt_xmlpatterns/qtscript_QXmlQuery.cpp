#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlquery.h>
#include <QVariant>
#include <qabstractmessagehandler.h>
#include <qabstracturiresolver.h>
#include <qabstractxmlnodemodel.h>
#include <qiodevice.h>
#include <qnetworkaccessmanager.h>
#include <qurl.h>
#include <qxmlname.h>
#include <qxmlnamepool.h>
#include <qxmlquery.h>
#include <qxmlresultitems.h>

static const char * const qtscript_QXmlQuery_function_names[] = {
    "QXmlQuery"
    // static
    // prototype
    , "bindVariable"
    , "evaluateTo"
    , "initialTemplateName"
    , "isValid"
    , "messageHandler"
    , "namePool"
    , "networkAccessManager"
    , "operator_assign"
    , "queryLanguage"
    , "setFocus"
    , "setInitialTemplateName"
    , "setMessageHandler"
    , "setNetworkAccessManager"
    , "setQuery"
    , "setUriResolver"
    , "uriResolver"
    , "toString"
};

static const char * const qtscript_QXmlQuery_function_signatures[] = {
    "\nQueryLanguage queryLanguage, QXmlNamePool np\nQXmlNamePool np\nQXmlQuery other"
    // static
    // prototype
    , "String localName, QIODevice arg__2\nString localName, QXmlItem value\nString localName, QXmlQuery query\nQXmlName name, QIODevice arg__2\nQXmlName name, QXmlItem value\nQXmlName name, QXmlQuery query"
    , "QIODevice target\nString output\nQXmlResultItems result"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QXmlQuery other"
    , ""
    , "QIODevice document\nString focus\nQUrl documentURI\nQXmlItem item"
    , "String name\nQXmlName name"
    , "QAbstractMessageHandler messageHandler"
    , "QNetworkAccessManager newManager"
    , "QIODevice sourceCode, QUrl documentURI\nString sourceCode, QUrl documentURI\nQUrl queryURI, QUrl baseURI"
    , "QAbstractUriResolver resolver"
    , ""
""
};

static const int qtscript_QXmlQuery_function_lengths[] = {
    2
    // static
    // prototype
    , 2
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
    , 1
    , 1
    , 2
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QXmlQuery_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlQuery::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlQuery)
Q_DECLARE_METATYPE(QXmlQuery*)
Q_DECLARE_METATYPE(QXmlQuery::QueryLanguage)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QString*)
Q_DECLARE_METATYPE(QXmlResultItems*)
Q_DECLARE_METATYPE(QAbstractMessageHandler*)
Q_DECLARE_METATYPE(QXmlNamePool)
Q_DECLARE_METATYPE(QNetworkAccessManager*)
Q_DECLARE_METATYPE(QAbstractUriResolver*)

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
// QXmlQuery::QueryLanguage
//

static const QXmlQuery::QueryLanguage qtscript_QXmlQuery_QueryLanguage_values[] = {
    QXmlQuery::XQuery10
    , QXmlQuery::XSLT20
    , QXmlQuery::XmlSchema11IdentityConstraintSelector
    , QXmlQuery::XmlSchema11IdentityConstraintField
    , QXmlQuery::XPath20
};

static const char * const qtscript_QXmlQuery_QueryLanguage_keys[] = {
    "XQuery10"
    , "XSLT20"
    , "XmlSchema11IdentityConstraintSelector"
    , "XmlSchema11IdentityConstraintField"
    , "XPath20"
};

static QString qtscript_QXmlQuery_QueryLanguage_toStringHelper(QXmlQuery::QueryLanguage value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QXmlQuery_QueryLanguage_values[i] == value)
            return QString::fromLatin1(qtscript_QXmlQuery_QueryLanguage_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QXmlQuery_QueryLanguage_toScriptValue(QScriptEngine *engine, const QXmlQuery::QueryLanguage &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QXmlQuery"));
    return clazz.property(qtscript_QXmlQuery_QueryLanguage_toStringHelper(value));
}

static void qtscript_QXmlQuery_QueryLanguage_fromScriptValue(const QScriptValue &value, QXmlQuery::QueryLanguage &out)
{
    out = qvariant_cast<QXmlQuery::QueryLanguage>(value.toVariant());
}

static QScriptValue qtscript_construct_QXmlQuery_QueryLanguage(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QXmlQuery_QueryLanguage_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QXmlQuery::QueryLanguage>(arg));
    }
    return context->throwError(QString::fromLatin1("QueryLanguage(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QXmlQuery_QueryLanguage_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QXmlQuery::QueryLanguage value = qscriptvalue_cast<QXmlQuery::QueryLanguage>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QXmlQuery_QueryLanguage_toString(QScriptContext *context, QScriptEngine *engine)
{
    QXmlQuery::QueryLanguage value = qscriptvalue_cast<QXmlQuery::QueryLanguage>(context->thisObject());
    return QScriptValue(engine, qtscript_QXmlQuery_QueryLanguage_toStringHelper(value));
}

static QScriptValue qtscript_create_QXmlQuery_QueryLanguage_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QXmlQuery_QueryLanguage,
        qtscript_QXmlQuery_QueryLanguage_valueOf, qtscript_QXmlQuery_QueryLanguage_toString);
    qScriptRegisterMetaType<QXmlQuery::QueryLanguage>(engine, qtscript_QXmlQuery_QueryLanguage_toScriptValue,
        qtscript_QXmlQuery_QueryLanguage_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QXmlQuery_QueryLanguage_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QXmlQuery_QueryLanguage_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QXmlQuery
//

static QScriptValue qtscript_QXmlQuery_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 16;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlQuery* _q_self = qscriptvalue_cast<QXmlQuery*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlQuery.%0(): this object is not a QXmlQuery")
            .arg(qtscript_QXmlQuery_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<QIODevice*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            _q_self->bindVariable(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QXmlItem>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QXmlItem _q_arg1 = qscriptvalue_cast<QXmlItem>(context->argument(1));
            _q_self->bindVariable(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QXmlQuery>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QXmlQuery _q_arg1 = qscriptvalue_cast<QXmlQuery>(context->argument(1));
            _q_self->bindVariable(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QXmlName>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QIODevice*>(context->argument(1))) {
            QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
            QIODevice* _q_arg1 = qscriptvalue_cast<QIODevice*>(context->argument(1));
            _q_self->bindVariable(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QXmlName>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QXmlItem>() == context->argument(1).toVariant().userType())) {
            QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
            QXmlItem _q_arg1 = qscriptvalue_cast<QXmlItem>(context->argument(1));
            _q_self->bindVariable(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QXmlName>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QXmlQuery>() == context->argument(1).toVariant().userType())) {
            QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
            QXmlQuery _q_arg1 = qscriptvalue_cast<QXmlQuery>(context->argument(1));
            _q_self->bindVariable(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_result = _q_self->evaluateTo(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QString*>(context->argument(0))) {
            QString* _q_arg0 = qscriptvalue_cast<QString*>(context->argument(0));
            bool _q_result = _q_self->evaluateTo(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QXmlResultItems*>(context->argument(0))) {
            QXmlResultItems* _q_arg0 = qscriptvalue_cast<QXmlResultItems*>(context->argument(0));
            _q_self->evaluateTo(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QXmlName _q_result = _q_self->initialTemplateName();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QAbstractMessageHandler* _q_result = _q_self->messageHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QXmlNamePool _q_result = _q_self->namePool();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QNetworkAccessManager* _q_result = _q_self->networkAccessManager();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QXmlQuery _q_arg0 = qscriptvalue_cast<QXmlQuery>(context->argument(0));
        QXmlQuery _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QXmlQuery::QueryLanguage _q_result = _q_self->queryLanguage();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            bool _q_result = _q_self->setFocus(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->setFocus(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            bool _q_result = _q_self->setFocus(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QXmlItem>() == context->argument(0).toVariant().userType())) {
            QXmlItem _q_arg0 = qscriptvalue_cast<QXmlItem>(context->argument(0));
            _q_self->setFocus(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setInitialTemplateName(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QXmlName>() == context->argument(0).toVariant().userType())) {
            QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
            _q_self->setInitialTemplateName(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QAbstractMessageHandler* _q_arg0 = qscriptvalue_cast<QAbstractMessageHandler*>(context->argument(0));
        _q_self->setMessageHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QNetworkAccessManager* _q_arg0 = qscriptvalue_cast<QNetworkAccessManager*>(context->argument(0));
        _q_self->setNetworkAccessManager(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            _q_self->setQuery(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setQuery(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            _q_self->setQuery(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QUrl>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
            _q_self->setQuery(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QUrl>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
            _q_self->setQuery(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QUrl>() == context->argument(1).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
            _q_self->setQuery(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QAbstractUriResolver* _q_arg0 = qscriptvalue_cast<QAbstractUriResolver*>(context->argument(0));
        _q_self->setUriResolver(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QAbstractUriResolver* _q_result = const_cast<QAbstractUriResolver*>(_q_self->uriResolver());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16: {
    QString result = QString::fromLatin1("QXmlQuery");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlQuery_throw_ambiguity_error_helper(context,
        qtscript_QXmlQuery_function_names[_id+1],
        qtscript_QXmlQuery_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlQuery_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlQuery(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlQuery _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QXmlQuery::QueryLanguage>() == context->argument(0).toVariant().userType())) {
            QXmlQuery::QueryLanguage _q_arg0 = qscriptvalue_cast<QXmlQuery::QueryLanguage>(context->argument(0));
            QXmlQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QXmlNamePool>() == context->argument(0).toVariant().userType())) {
            QXmlNamePool _q_arg0 = qscriptvalue_cast<QXmlNamePool>(context->argument(0));
            QXmlQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QXmlQuery>() == context->argument(0).toVariant().userType())) {
            QXmlQuery _q_arg0 = qscriptvalue_cast<QXmlQuery>(context->argument(0));
            QXmlQuery _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QXmlQuery::QueryLanguage _q_arg0 = qscriptvalue_cast<QXmlQuery::QueryLanguage>(context->argument(0));
        QXmlNamePool _q_arg1 = qscriptvalue_cast<QXmlNamePool>(context->argument(1));
        QXmlQuery _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlQuery_throw_ambiguity_error_helper(context,
        qtscript_QXmlQuery_function_names[_id],
        qtscript_QXmlQuery_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlQuery_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlQuery*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlQuery*)0));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlQuery_prototype_call, qtscript_QXmlQuery_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlQuery_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlQuery>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlQuery*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlQuery_static_call, proto, qtscript_QXmlQuery_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("QueryLanguage"),
        qtscript_create_QXmlQuery_QueryLanguage_class(engine, ctor));
    return ctor;
}
