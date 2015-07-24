#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractxmlnodemodel.h>
#include <QVariant>
#include <qabstractxmlnodemodel.h>

static const char * const qtscript_QXmlNodeModelIndex_function_names[] = {
    "QXmlNodeModelIndex"
    // static
    // prototype
    , "additionalData"
    , "data"
    , "isNull"
    , "model"
    , "equals"
    , "toString"
};

static const char * const qtscript_QXmlNodeModelIndex_function_signatures[] = {
    "\nQXmlNodeModelIndex other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QXmlNodeModelIndex other"
""
};

static const int qtscript_QXmlNodeModelIndex_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QXmlNodeModelIndex_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlNodeModelIndex::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlNodeModelIndex)
Q_DECLARE_METATYPE(QXmlNodeModelIndex*)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::NodeKind)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::DocumentOrder)
Q_DECLARE_METATYPE(QAbstractXmlNodeModel*)

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
// QXmlNodeModelIndex::NodeKind
//

static const QXmlNodeModelIndex::NodeKind qtscript_QXmlNodeModelIndex_NodeKind_values[] = {
    QXmlNodeModelIndex::Attribute
    , QXmlNodeModelIndex::Comment
    , QXmlNodeModelIndex::Document
    , QXmlNodeModelIndex::Element
    , QXmlNodeModelIndex::Namespace
    , QXmlNodeModelIndex::ProcessingInstruction
    , QXmlNodeModelIndex::Text
};

static const char * const qtscript_QXmlNodeModelIndex_NodeKind_keys[] = {
    "Attribute"
    , "Comment"
    , "Document"
    , "Element"
    , "Namespace"
    , "ProcessingInstruction"
    , "Text"
};

static QString qtscript_QXmlNodeModelIndex_NodeKind_toStringHelper(QXmlNodeModelIndex::NodeKind value)
{
    for (int i = 0; i < 7; ++i) {
        if (qtscript_QXmlNodeModelIndex_NodeKind_values[i] == value)
            return QString::fromLatin1(qtscript_QXmlNodeModelIndex_NodeKind_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QXmlNodeModelIndex_NodeKind_toScriptValue(QScriptEngine *engine, const QXmlNodeModelIndex::NodeKind &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QXmlNodeModelIndex"));
    return clazz.property(qtscript_QXmlNodeModelIndex_NodeKind_toStringHelper(value));
}

static void qtscript_QXmlNodeModelIndex_NodeKind_fromScriptValue(const QScriptValue &value, QXmlNodeModelIndex::NodeKind &out)
{
    out = qvariant_cast<QXmlNodeModelIndex::NodeKind>(value.toVariant());
}

static QScriptValue qtscript_construct_QXmlNodeModelIndex_NodeKind(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 7; ++i) {
        if (qtscript_QXmlNodeModelIndex_NodeKind_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QXmlNodeModelIndex::NodeKind>(arg));
    }
    return context->throwError(QString::fromLatin1("NodeKind(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QXmlNodeModelIndex_NodeKind_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QXmlNodeModelIndex::NodeKind value = qscriptvalue_cast<QXmlNodeModelIndex::NodeKind>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QXmlNodeModelIndex_NodeKind_toString(QScriptContext *context, QScriptEngine *engine)
{
    QXmlNodeModelIndex::NodeKind value = qscriptvalue_cast<QXmlNodeModelIndex::NodeKind>(context->thisObject());
    return QScriptValue(engine, qtscript_QXmlNodeModelIndex_NodeKind_toStringHelper(value));
}

static QScriptValue qtscript_create_QXmlNodeModelIndex_NodeKind_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QXmlNodeModelIndex_NodeKind,
        qtscript_QXmlNodeModelIndex_NodeKind_valueOf, qtscript_QXmlNodeModelIndex_NodeKind_toString);
    qScriptRegisterMetaType<QXmlNodeModelIndex::NodeKind>(engine, qtscript_QXmlNodeModelIndex_NodeKind_toScriptValue,
        qtscript_QXmlNodeModelIndex_NodeKind_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QXmlNodeModelIndex_NodeKind_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QXmlNodeModelIndex_NodeKind_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QXmlNodeModelIndex::DocumentOrder
//

static const QXmlNodeModelIndex::DocumentOrder qtscript_QXmlNodeModelIndex_DocumentOrder_values[] = {
    QXmlNodeModelIndex::Precedes
    , QXmlNodeModelIndex::Is
    , QXmlNodeModelIndex::Follows
};

static const char * const qtscript_QXmlNodeModelIndex_DocumentOrder_keys[] = {
    "Precedes"
    , "Is"
    , "Follows"
};

static QString qtscript_QXmlNodeModelIndex_DocumentOrder_toStringHelper(QXmlNodeModelIndex::DocumentOrder value)
{
    if ((value >= QXmlNodeModelIndex::Precedes) && (value <= QXmlNodeModelIndex::Follows))
        return qtscript_QXmlNodeModelIndex_DocumentOrder_keys[static_cast<int>(value)-static_cast<int>(QXmlNodeModelIndex::Precedes)];
    return QString();
}

static QScriptValue qtscript_QXmlNodeModelIndex_DocumentOrder_toScriptValue(QScriptEngine *engine, const QXmlNodeModelIndex::DocumentOrder &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QXmlNodeModelIndex"));
    return clazz.property(qtscript_QXmlNodeModelIndex_DocumentOrder_toStringHelper(value));
}

static void qtscript_QXmlNodeModelIndex_DocumentOrder_fromScriptValue(const QScriptValue &value, QXmlNodeModelIndex::DocumentOrder &out)
{
    out = qvariant_cast<QXmlNodeModelIndex::DocumentOrder>(value.toVariant());
}

static QScriptValue qtscript_construct_QXmlNodeModelIndex_DocumentOrder(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QXmlNodeModelIndex::Precedes) && (arg <= QXmlNodeModelIndex::Follows))
        return qScriptValueFromValue(engine,  static_cast<QXmlNodeModelIndex::DocumentOrder>(arg));
    return context->throwError(QString::fromLatin1("DocumentOrder(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QXmlNodeModelIndex_DocumentOrder_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QXmlNodeModelIndex::DocumentOrder value = qscriptvalue_cast<QXmlNodeModelIndex::DocumentOrder>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QXmlNodeModelIndex_DocumentOrder_toString(QScriptContext *context, QScriptEngine *engine)
{
    QXmlNodeModelIndex::DocumentOrder value = qscriptvalue_cast<QXmlNodeModelIndex::DocumentOrder>(context->thisObject());
    return QScriptValue(engine, qtscript_QXmlNodeModelIndex_DocumentOrder_toStringHelper(value));
}

static QScriptValue qtscript_create_QXmlNodeModelIndex_DocumentOrder_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QXmlNodeModelIndex_DocumentOrder,
        qtscript_QXmlNodeModelIndex_DocumentOrder_valueOf, qtscript_QXmlNodeModelIndex_DocumentOrder_toString);
    qScriptRegisterMetaType<QXmlNodeModelIndex::DocumentOrder>(engine, qtscript_QXmlNodeModelIndex_DocumentOrder_toScriptValue,
        qtscript_QXmlNodeModelIndex_DocumentOrder_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QXmlNodeModelIndex_DocumentOrder_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QXmlNodeModelIndex_DocumentOrder_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QXmlNodeModelIndex
//

static QScriptValue qtscript_QXmlNodeModelIndex_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlNodeModelIndex* _q_self = qscriptvalue_cast<QXmlNodeModelIndex*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlNodeModelIndex.%0(): this object is not a QXmlNodeModelIndex")
            .arg(qtscript_QXmlNodeModelIndex_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->additionalData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->data();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QAbstractXmlNodeModel* _q_result = const_cast<QAbstractXmlNodeModel*>(_q_self->model());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QXmlNodeModelIndex");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlNodeModelIndex_throw_ambiguity_error_helper(context,
        qtscript_QXmlNodeModelIndex_function_names[_id+1],
        qtscript_QXmlNodeModelIndex_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlNodeModelIndex_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlNodeModelIndex(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QXmlNodeModelIndex _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QXmlNodeModelIndex _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlNodeModelIndex_throw_ambiguity_error_helper(context,
        qtscript_QXmlNodeModelIndex_function_names[_id],
        qtscript_QXmlNodeModelIndex_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlNodeModelIndex_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlNodeModelIndex*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlNodeModelIndex*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlNodeModelIndex_prototype_call, qtscript_QXmlNodeModelIndex_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlNodeModelIndex_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlNodeModelIndex>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QXmlNodeModelIndex*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlNodeModelIndex_static_call, proto, qtscript_QXmlNodeModelIndex_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("NodeKind"),
        qtscript_create_QXmlNodeModelIndex_NodeKind_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DocumentOrder"),
        qtscript_create_QXmlNodeModelIndex_DocumentOrder_class(engine, ctor));
    return ctor;
}
