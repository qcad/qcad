#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qxmlstream.h>
#include <QVariant>
#include <qlist.h>
#include <qvector.h>
#include <qxmlstream.h>

#include "qtscriptshell_QXmlStreamAttributes.h"

static const char * const qtscript_QXmlStreamAttributes_function_names[] = {
    "QXmlStreamAttributes"
    // static
    , "fromList"
    // prototype
    , "append"
    , "at"
    , "capacity"
    , "clear"
    , "contains"
    , "count"
    , "empty"
    , "endsWith"
    , "fill"
    , "first"
    , "hasAttribute"
    , "indexOf"
    , "isEmpty"
    , "isSharedWith"
    , "last"
    , "lastIndexOf"
    , "mid"
    , "equals"
    , "prepend"
    , "remove"
    , "replace"
    , "reserve"
    , "resize"
    , "setSharable"
    , "size"
    , "squeeze"
    , "startsWith"
    , "toList"
    , "value"
    , "toString"
};

static const char * const qtscript_QXmlStreamAttributes_function_signatures[] = {
    ""
    // static
    , "List list"
    // prototype
    , "String namespaceUri, String name, String value\nString qualifiedName, String value\nQXmlStreamAttribute attribute"
    , "int i"
    , ""
    , ""
    , "QXmlStreamAttribute t"
    , "\nQXmlStreamAttribute t"
    , ""
    , "QXmlStreamAttribute t"
    , "QXmlStreamAttribute t, int size"
    , ""
    , "String namespaceUri, String name\nString qualifiedName"
    , "QXmlStreamAttribute t, int from"
    , ""
    , "List other"
    , ""
    , "QXmlStreamAttribute t, int from"
    , "int pos, int length"
    , "List v"
    , "QXmlStreamAttribute t"
    , "int i\nint i, int n"
    , "int i, QXmlStreamAttribute t"
    , "int size"
    , "int size"
    , "bool sharable"
    , ""
    , ""
    , "QXmlStreamAttribute t"
    , ""
    , "String namespaceUri, String name\nString qualifiedName"
""
};

static const int qtscript_QXmlStreamAttributes_function_lengths[] = {
    0
    // static
    , 1
    // prototype
    , 3
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 2
    , 0
    , 2
    , 2
    , 0
    , 1
    , 0
    , 2
    , 2
    , 1
    , 1
    , 2
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_QXmlStreamAttributes_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlStreamAttributes::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlStreamAttributes)
Q_DECLARE_METATYPE(QXmlStreamAttributes*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlStreamAttributes)
Q_DECLARE_METATYPE(QtScriptShell_QXmlStreamAttributes*)
Q_DECLARE_METATYPE(QXmlStreamAttribute)
Q_DECLARE_METATYPE(QVector<QXmlStreamAttribute>)
Q_DECLARE_METATYPE(QList<QXmlStreamAttribute>)
Q_DECLARE_METATYPE(QStringRef)

//
// QXmlStreamAttributes
//

static QScriptValue qtscript_QXmlStreamAttributes_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QXmlStreamAttributes* _q_self = qscriptvalue_cast<QXmlStreamAttributes*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlStreamAttributes.%0(): this object is not a QXmlStreamAttributes")
            .arg(qtscript_QXmlStreamAttributes_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        _q_self->append(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->append(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        _q_self->append(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QXmlStreamAttribute _q_result = _q_self->at(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->capacity();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        int _q_result = _q_self->count(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->empty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        bool _q_result = _q_self->endsWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        QVector<QXmlStreamAttribute> _q_result = _q_self->fill(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVector<QXmlStreamAttribute> _q_result = _q_self->fill(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QXmlStreamAttribute _q_result = _q_self->first();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasAttribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->hasAttribute(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->indexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QVector<QXmlStreamAttribute> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        bool _q_result = _q_self->isSharedWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QXmlStreamAttribute _q_result = _q_self->last();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        int _q_result = _q_self->lastIndexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->lastIndexOf(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVector<QXmlStreamAttribute> _q_result = _q_self->mid(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QVector<QXmlStreamAttribute> _q_result = _q_self->mid(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QVector<QXmlStreamAttribute> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        _q_self->prepend(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->remove(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->remove(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QXmlStreamAttribute _q_arg1 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(1));
        _q_self->replace(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->reserve(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->resize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSharable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        _q_self->squeeze();
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QXmlStreamAttribute _q_arg0 = qscriptvalue_cast<QXmlStreamAttribute>(context->argument(0));
        bool _q_result = _q_self->startsWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QList<QXmlStreamAttribute> _q_result = _q_self->toList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringRef _q_result = _q_self->value(_q_arg0);
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QStringRef _q_result = _q_self->value(_q_arg0, _q_arg1);
        
            // TEMPLATE - core.convert_stringref_to_string - START
            QString _q_convertedResult = _q_result.toString();
    // TEMPLATE - core.convert_stringref_to_string - END
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 29: {
    QString result = QString::fromLatin1("QXmlStreamAttributes");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamAttributes_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamAttributes_function_names[_id+2],
        qtscript_QXmlStreamAttributes_function_signatures[_id+2]);
}

static QScriptValue qtscript_QXmlStreamAttributes_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlStreamAttributes(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlStreamAttributes _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlStreamAttributes)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QList<QXmlStreamAttribute> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QVector<QXmlStreamAttribute> _q_result = QXmlStreamAttributes::fromList(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlStreamAttributes_throw_ambiguity_error_helper(context,
        qtscript_QXmlStreamAttributes_function_names[_id],
        qtscript_QXmlStreamAttributes_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlStreamAttributes_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamAttributes*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlStreamAttributes*)0));
    for (int i = 0; i < 30; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamAttributes_prototype_call, qtscript_QXmlStreamAttributes_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlStreamAttributes_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamAttributes>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlStreamAttributes*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlStreamAttributes_static_call, proto, qtscript_QXmlStreamAttributes_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlStreamAttributes_static_call,
            qtscript_QXmlStreamAttributes_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QXmlStreamAttributes_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
