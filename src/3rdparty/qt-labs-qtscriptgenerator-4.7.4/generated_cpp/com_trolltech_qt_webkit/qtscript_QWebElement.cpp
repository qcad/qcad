#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwebelement.h>
#include <QVariant>
#include <qpainter.h>
#include <qrect.h>
#include <qstringlist.h>
#include <qwebelement.h>
#include <qwebframe.h>

static const char * const qtscript_QWebElement_function_names[] = {
    "QWebElement"
    // static
    // prototype
    , "addClass"
    , "appendInside"
    , "appendOutside"
    , "attribute"
    , "attributeNS"
    , "attributeNames"
    , "classes"
    , "clone"
    , "document"
    , "encloseContentsWith"
    , "encloseWith"
    , "evaluateJavaScript"
    , "findFirst"
    , "firstChild"
    , "geometry"
    , "hasAttribute"
    , "hasAttributeNS"
    , "hasAttributes"
    , "hasClass"
    , "hasFocus"
    , "isNull"
    , "lastChild"
    , "localName"
    , "namespaceUri"
    , "nextSibling"
    , "operator_assign"
    , "equals"
    , "parent"
    , "prefix"
    , "prependInside"
    , "prependOutside"
    , "previousSibling"
    , "removeAllChildren"
    , "removeAttribute"
    , "removeAttributeNS"
    , "removeClass"
    , "removeFromDocument"
    , "render"
    , "replace"
    , "setAttribute"
    , "setAttributeNS"
    , "setFocus"
    , "setInnerXml"
    , "setOuterXml"
    , "setPlainText"
    , "setStyleProperty"
    , "styleProperty"
    , "tagName"
    , "takeFromDocument"
    , "toInnerXml"
    , "toOuterXml"
    , "toPlainText"
    , "toggleClass"
    , "webFrame"
    , "toString"
};

static const char * const qtscript_QWebElement_function_signatures[] = {
    "\nQWebElement arg__1"
    // static
    // prototype
    , "String name"
    , "String markup\nQWebElement element"
    , "String markup\nQWebElement element"
    , "String name, String defaultValue"
    , "String namespaceUri, String name, String defaultValue"
    , "String namespaceUri"
    , ""
    , ""
    , ""
    , "String markup\nQWebElement element"
    , "String markup\nQWebElement element"
    , "String scriptSource"
    , "String selectorQuery"
    , ""
    , ""
    , "String name"
    , "String namespaceUri, String name"
    , ""
    , "String name"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QWebElement arg__1"
    , "QWebElement o"
    , ""
    , ""
    , "String markup\nQWebElement element"
    , "String markup\nQWebElement element"
    , ""
    , ""
    , "String name"
    , "String namespaceUri, String name"
    , "String name"
    , ""
    , "QPainter painter"
    , "String markup\nQWebElement element"
    , "String name, String value"
    , "String namespaceUri, String name, String value"
    , ""
    , "String markup"
    , "String markup"
    , "String text"
    , "String name, String value"
    , "String name, StyleResolveStrategy strategy"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String name"
    , ""
""
};

static const int qtscript_QWebElement_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 2
    , 3
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 2
    , 0
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
    , 0
    , 1
    , 1
    , 0
    , 0
    , 1
    , 2
    , 1
    , 0
    , 1
    , 1
    , 2
    , 3
    , 0
    , 1
    , 1
    , 1
    , 2
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QWebElement_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebElement::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebElement*)
Q_DECLARE_METATYPE(QWebElement::StyleResolveStrategy)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QWebFrame*)

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
// QWebElement::StyleResolveStrategy
//

static const QWebElement::StyleResolveStrategy qtscript_QWebElement_StyleResolveStrategy_values[] = {
    QWebElement::InlineStyle
    , QWebElement::CascadedStyle
    , QWebElement::ComputedStyle
};

static const char * const qtscript_QWebElement_StyleResolveStrategy_keys[] = {
    "InlineStyle"
    , "CascadedStyle"
    , "ComputedStyle"
};

static QString qtscript_QWebElement_StyleResolveStrategy_toStringHelper(QWebElement::StyleResolveStrategy value)
{
    if ((value >= QWebElement::InlineStyle) && (value <= QWebElement::ComputedStyle))
        return qtscript_QWebElement_StyleResolveStrategy_keys[static_cast<int>(value)-static_cast<int>(QWebElement::InlineStyle)];
    return QString();
}

static QScriptValue qtscript_QWebElement_StyleResolveStrategy_toScriptValue(QScriptEngine *engine, const QWebElement::StyleResolveStrategy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebElement"));
    return clazz.property(qtscript_QWebElement_StyleResolveStrategy_toStringHelper(value));
}

static void qtscript_QWebElement_StyleResolveStrategy_fromScriptValue(const QScriptValue &value, QWebElement::StyleResolveStrategy &out)
{
    out = qvariant_cast<QWebElement::StyleResolveStrategy>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebElement_StyleResolveStrategy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWebElement::InlineStyle) && (arg <= QWebElement::ComputedStyle))
        return qScriptValueFromValue(engine,  static_cast<QWebElement::StyleResolveStrategy>(arg));
    return context->throwError(QString::fromLatin1("StyleResolveStrategy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebElement_StyleResolveStrategy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebElement::StyleResolveStrategy value = qscriptvalue_cast<QWebElement::StyleResolveStrategy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebElement_StyleResolveStrategy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebElement::StyleResolveStrategy value = qscriptvalue_cast<QWebElement::StyleResolveStrategy>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebElement_StyleResolveStrategy_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebElement_StyleResolveStrategy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebElement_StyleResolveStrategy,
        qtscript_QWebElement_StyleResolveStrategy_valueOf, qtscript_QWebElement_StyleResolveStrategy_toString);
    qScriptRegisterMetaType<QWebElement::StyleResolveStrategy>(engine, qtscript_QWebElement_StyleResolveStrategy_toScriptValue,
        qtscript_QWebElement_StyleResolveStrategy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebElement_StyleResolveStrategy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebElement_StyleResolveStrategy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebElement
//

static QScriptValue qtscript_QWebElement_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 54;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWebElement* _q_self = qscriptvalue_cast<QWebElement*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebElement.%0(): this object is not a QWebElement")
            .arg(qtscript_QWebElement_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->addClass(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->appendInside(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QWebElement>() == context->argument(0).toVariant().userType())) {
            QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
            _q_self->appendInside(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->appendOutside(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QWebElement>() == context->argument(0).toVariant().userType())) {
            QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
            _q_self->appendOutside(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 3:
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

    case 4:
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

    case 5:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->attributeNames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = _q_self->attributeNames(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->classes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->clone();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->document();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->encloseContentsWith(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QWebElement>() == context->argument(0).toVariant().userType())) {
            QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
            _q_self->encloseContentsWith(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->encloseWith(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QWebElement>() == context->argument(0).toVariant().userType())) {
            QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
            _q_self->encloseWith(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_result = _q_self->evaluateJavaScript(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QWebElement _q_result = _q_self->findFirst(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->firstChild();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->geometry();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasAttribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->hasAttributeNS(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasAttributes();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasClass(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasFocus();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->lastChild();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->localName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->namespaceUri();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->nextSibling();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
        QWebElement _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->parent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->prefix();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->prependInside(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QWebElement>() == context->argument(0).toVariant().userType())) {
            QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
            _q_self->prependInside(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->prependOutside(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QWebElement>() == context->argument(0).toVariant().userType())) {
            QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
            _q_self->prependOutside(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->previousSibling();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        _q_self->removeAllChildren();
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeAttribute(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->removeAttributeNS(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeClass(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        _q_self->removeFromDocument();
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        _q_self->render(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->replace(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QWebElement>() == context->argument(0).toVariant().userType())) {
            QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
            _q_self->replace(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 39:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setAttribute(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        _q_self->setAttributeNS(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        _q_self->setFocus();
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setInnerXml(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setOuterXml(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPlainText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setStyleProperty(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWebElement::StyleResolveStrategy _q_arg1 = qscriptvalue_cast<QWebElement::StyleResolveStrategy>(context->argument(1));
        QString _q_result = _q_self->styleProperty(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->tagName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->takeFromDocument();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toInnerXml();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toOuterXml();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toPlainText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->toggleClass(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 0) {
        QWebFrame* _q_result = _q_self->webFrame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 54: {
    QString result = QString::fromLatin1("QWebElement");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebElement_throw_ambiguity_error_helper(context,
        qtscript_QWebElement_function_names[_id+1],
        qtscript_QWebElement_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebElement_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebElement(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QWebElement _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWebElement _q_arg0 = qscriptvalue_cast<QWebElement>(context->argument(0));
        QWebElement _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebElement_throw_ambiguity_error_helper(context,
        qtscript_QWebElement_function_names[_id],
        qtscript_QWebElement_function_signatures[_id]);
}

QScriptValue qtscript_create_QWebElement_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebElement*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebElement*)0));
    for (int i = 0; i < 55; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebElement_prototype_call, qtscript_QWebElement_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebElement_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWebElement>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QWebElement*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebElement_static_call, proto, qtscript_QWebElement_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleResolveStrategy"),
        qtscript_create_QWebElement_StyleResolveStrategy_class(engine, ctor));
    return ctor;
}
