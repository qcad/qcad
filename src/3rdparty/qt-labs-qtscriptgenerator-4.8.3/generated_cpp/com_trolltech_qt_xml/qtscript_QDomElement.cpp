#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdom.h>
#include <QVariant>
#include <qdom.h>
#include <qtextstream.h>

static const char * const qtscript_QDomElement_function_names[] = {
    "QDomElement"
    // static
    // prototype
    , "attribute"
    , "attributeNS"
    , "attributeNode"
    , "attributeNodeNS"
    , "attributes"
    , "elementsByTagName"
    , "elementsByTagNameNS"
    , "hasAttribute"
    , "hasAttributeNS"
    , "removeAttribute"
    , "removeAttributeNS"
    , "removeAttributeNode"
    , "setAttribute"
    , "setAttributeNS"
    , "setAttributeNode"
    , "setAttributeNodeNS"
    , "setTagName"
    , "tagName"
    , "text"
    , "toString"
};

static const char * const qtscript_QDomElement_function_signatures[] = {
    "\nQDomElement x"
    // static
    // prototype
    , "String name, String defValue"
    , "String nsURI, String localName, String defValue"
    , "String name"
    , "String nsURI, String localName"
    , ""
    , "String tagname"
    , "String nsURI, String localName"
    , "String name"
    , "String nsURI, String localName"
    , "String name"
    , "String nsURI, String localName"
    , "QDomAttr oldAttr"
    , "String name, String value\nString name, double value\nString name, float value\nString name, int value\nString name, qlonglong value"
    , "String nsURI, String qName, String value\nString nsURI, String qName, double value\nString nsURI, String qName, int value\nString nsURI, String qName, qlonglong value"
    , "QDomAttr newAttr"
    , "QDomAttr newAttr"
    , "String name"
    , ""
    , ""
""
};

static const int qtscript_QDomElement_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 3
    , 1
    , 2
    , 0
    , 1
    , 2
    , 1
    , 2
    , 1
    , 2
    , 1
    , 2
    , 3
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QDomElement_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomElement::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomElement)
Q_DECLARE_METATYPE(QDomElement*)
Q_DECLARE_METATYPE(QDomAttr)
Q_DECLARE_METATYPE(QDomNamedNodeMap)
Q_DECLARE_METATYPE(QDomNodeList)
Q_DECLARE_METATYPE(QDomNode*)

//
// QDomElement
//

static QScriptValue qtscript_QDomElement_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDomElement* _q_self = qscriptvalue_cast<QDomElement*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomElement.%0(): this object is not a QDomElement")
            .arg(qtscript_QDomElement_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->attribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = _q_self->attribute(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_result = _q_self->attributeNS(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_result = _q_self->attributeNS(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomAttr _q_result = _q_self->attributeNode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDomAttr _q_result = _q_self->attributeNodeNS(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QDomNamedNodeMap _q_result = _q_self->attributes();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDomNodeList _q_result = _q_self->elementsByTagName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QDomNodeList _q_result = _q_self->elementsByTagNameNS(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasAttribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->hasAttributeNS(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeAttribute(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->removeAttributeNS(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QDomAttr _q_arg0 = qscriptvalue_cast<QDomAttr>(context->argument(0));
        QDomAttr _q_result = _q_self->removeAttributeNode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            _q_self->setAttribute(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            double _q_arg1 = context->argument(1).toNumber();
            _q_self->setAttribute(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            _q_self->setAttribute(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->setAttribute(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && (qMetaTypeId<qlonglong>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            qlonglong _q_arg1 = qscriptvalue_cast<qlonglong>(context->argument(1));
            _q_self->setAttribute(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 13:
    if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            _q_self->setAttributeNS(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            double _q_arg2 = context->argument(2).toNumber();
            _q_self->setAttributeNS(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeNS(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && (qMetaTypeId<qlonglong>() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            qlonglong _q_arg2 = qscriptvalue_cast<qlonglong>(context->argument(2));
            _q_self->setAttributeNS(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QDomAttr _q_arg0 = qscriptvalue_cast<QDomAttr>(context->argument(0));
        QDomAttr _q_result = _q_self->setAttributeNode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QDomAttr _q_arg0 = qscriptvalue_cast<QDomAttr>(context->argument(0));
        QDomAttr _q_result = _q_self->setAttributeNodeNS(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setTagName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->tagName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19: {
    QString result = QString::fromLatin1("QDomElement");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomElement_throw_ambiguity_error_helper(context,
        qtscript_QDomElement_function_names[_id+1],
        qtscript_QDomElement_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomElement_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomElement(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomElement _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomElement _q_arg0 = qscriptvalue_cast<QDomElement>(context->argument(0));
        QDomElement _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomElement_throw_ambiguity_error_helper(context,
        qtscript_QDomElement_function_names[_id],
        qtscript_QDomElement_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomElement_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomElement*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomElement*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDomNode*>()));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomElement_prototype_call, qtscript_QDomElement_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomElement_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomElement>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomElement*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomElement_static_call, proto, qtscript_QDomElement_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
