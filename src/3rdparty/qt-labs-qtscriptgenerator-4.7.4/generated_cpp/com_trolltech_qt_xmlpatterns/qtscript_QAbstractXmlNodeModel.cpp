#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractxmlnodemodel.h>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qsourcelocation.h>
#include <qurl.h>
#include <qvector.h>
#include <qxmlname.h>

#include "qtscriptshell_QAbstractXmlNodeModel.h"

static const char * const qtscript_QAbstractXmlNodeModel_function_names[] = {
    "QAbstractXmlNodeModel"
    // static
    // prototype
    , "baseUri"
    , "compareOrder"
    , "documentUri"
    , "elementById"
    , "kind"
    , "name"
    , "namespaceBindings"
    , "nodesByIdref"
    , "root"
    , "sourceLocation"
    , "stringValue"
    , "typedValue"
    , "toString"
};

static const char * const qtscript_QAbstractXmlNodeModel_function_signatures[] = {
    ""
    // static
    // prototype
    , "QXmlNodeModelIndex ni"
    , "QXmlNodeModelIndex ni1, QXmlNodeModelIndex ni2"
    , "QXmlNodeModelIndex ni"
    , "QXmlName NCName"
    , "QXmlNodeModelIndex ni"
    , "QXmlNodeModelIndex ni"
    , "QXmlNodeModelIndex n"
    , "QXmlName NCName"
    , "QXmlNodeModelIndex n"
    , "QXmlNodeModelIndex index"
    , "QXmlNodeModelIndex n"
    , "QXmlNodeModelIndex n"
""
};

static const int qtscript_QAbstractXmlNodeModel_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractXmlNodeModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractXmlNodeModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractXmlNodeModel*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractXmlNodeModel*)
Q_DECLARE_METATYPE(QAbstractXmlNodeModel::SimpleAxis)
Q_DECLARE_METATYPE(QAbstractXmlNodeModel::NodeCopySetting)
Q_DECLARE_METATYPE(QXmlNodeModelIndex)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::DocumentOrder)
Q_DECLARE_METATYPE(QXmlNodeModelIndex::NodeKind)
Q_DECLARE_METATYPE(QVector<QXmlName>)
Q_DECLARE_METATYPE(QVector<QXmlNodeModelIndex>)

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
// QAbstractXmlNodeModel::SimpleAxis
//

static const QAbstractXmlNodeModel::SimpleAxis qtscript_QAbstractXmlNodeModel_SimpleAxis_values[] = {
    QAbstractXmlNodeModel::Parent
    , QAbstractXmlNodeModel::FirstChild
    , QAbstractXmlNodeModel::PreviousSibling
    , QAbstractXmlNodeModel::NextSibling
};

static const char * const qtscript_QAbstractXmlNodeModel_SimpleAxis_keys[] = {
    "Parent"
    , "FirstChild"
    , "PreviousSibling"
    , "NextSibling"
};

static QString qtscript_QAbstractXmlNodeModel_SimpleAxis_toStringHelper(QAbstractXmlNodeModel::SimpleAxis value)
{
    if ((value >= QAbstractXmlNodeModel::Parent) && (value <= QAbstractXmlNodeModel::NextSibling))
        return qtscript_QAbstractXmlNodeModel_SimpleAxis_keys[static_cast<int>(value)-static_cast<int>(QAbstractXmlNodeModel::Parent)];
    return QString();
}

static QScriptValue qtscript_QAbstractXmlNodeModel_SimpleAxis_toScriptValue(QScriptEngine *engine, const QAbstractXmlNodeModel::SimpleAxis &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractXmlNodeModel"));
    return clazz.property(qtscript_QAbstractXmlNodeModel_SimpleAxis_toStringHelper(value));
}

static void qtscript_QAbstractXmlNodeModel_SimpleAxis_fromScriptValue(const QScriptValue &value, QAbstractXmlNodeModel::SimpleAxis &out)
{
    out = qvariant_cast<QAbstractXmlNodeModel::SimpleAxis>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractXmlNodeModel_SimpleAxis(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractXmlNodeModel::Parent) && (arg <= QAbstractXmlNodeModel::NextSibling))
        return qScriptValueFromValue(engine,  static_cast<QAbstractXmlNodeModel::SimpleAxis>(arg));
    return context->throwError(QString::fromLatin1("SimpleAxis(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractXmlNodeModel_SimpleAxis_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractXmlNodeModel::SimpleAxis value = qscriptvalue_cast<QAbstractXmlNodeModel::SimpleAxis>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractXmlNodeModel_SimpleAxis_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractXmlNodeModel::SimpleAxis value = qscriptvalue_cast<QAbstractXmlNodeModel::SimpleAxis>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractXmlNodeModel_SimpleAxis_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractXmlNodeModel_SimpleAxis_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractXmlNodeModel_SimpleAxis,
        qtscript_QAbstractXmlNodeModel_SimpleAxis_valueOf, qtscript_QAbstractXmlNodeModel_SimpleAxis_toString);
    qScriptRegisterMetaType<QAbstractXmlNodeModel::SimpleAxis>(engine, qtscript_QAbstractXmlNodeModel_SimpleAxis_toScriptValue,
        qtscript_QAbstractXmlNodeModel_SimpleAxis_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractXmlNodeModel_SimpleAxis_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractXmlNodeModel_SimpleAxis_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractXmlNodeModel::NodeCopySetting
//

static const QAbstractXmlNodeModel::NodeCopySetting qtscript_QAbstractXmlNodeModel_NodeCopySetting_values[] = {
    QAbstractXmlNodeModel::InheritNamespaces
    , QAbstractXmlNodeModel::PreserveNamespaces
};

static const char * const qtscript_QAbstractXmlNodeModel_NodeCopySetting_keys[] = {
    "InheritNamespaces"
    , "PreserveNamespaces"
};

static QString qtscript_QAbstractXmlNodeModel_NodeCopySetting_toStringHelper(QAbstractXmlNodeModel::NodeCopySetting value)
{
    if ((value >= QAbstractXmlNodeModel::InheritNamespaces) && (value <= QAbstractXmlNodeModel::PreserveNamespaces))
        return qtscript_QAbstractXmlNodeModel_NodeCopySetting_keys[static_cast<int>(value)-static_cast<int>(QAbstractXmlNodeModel::InheritNamespaces)];
    return QString();
}

static QScriptValue qtscript_QAbstractXmlNodeModel_NodeCopySetting_toScriptValue(QScriptEngine *engine, const QAbstractXmlNodeModel::NodeCopySetting &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractXmlNodeModel"));
    return clazz.property(qtscript_QAbstractXmlNodeModel_NodeCopySetting_toStringHelper(value));
}

static void qtscript_QAbstractXmlNodeModel_NodeCopySetting_fromScriptValue(const QScriptValue &value, QAbstractXmlNodeModel::NodeCopySetting &out)
{
    out = qvariant_cast<QAbstractXmlNodeModel::NodeCopySetting>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractXmlNodeModel_NodeCopySetting(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractXmlNodeModel::InheritNamespaces) && (arg <= QAbstractXmlNodeModel::PreserveNamespaces))
        return qScriptValueFromValue(engine,  static_cast<QAbstractXmlNodeModel::NodeCopySetting>(arg));
    return context->throwError(QString::fromLatin1("NodeCopySetting(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractXmlNodeModel_NodeCopySetting_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractXmlNodeModel::NodeCopySetting value = qscriptvalue_cast<QAbstractXmlNodeModel::NodeCopySetting>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractXmlNodeModel_NodeCopySetting_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractXmlNodeModel::NodeCopySetting value = qscriptvalue_cast<QAbstractXmlNodeModel::NodeCopySetting>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractXmlNodeModel_NodeCopySetting_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractXmlNodeModel_NodeCopySetting_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractXmlNodeModel_NodeCopySetting,
        qtscript_QAbstractXmlNodeModel_NodeCopySetting_valueOf, qtscript_QAbstractXmlNodeModel_NodeCopySetting_toString);
    qScriptRegisterMetaType<QAbstractXmlNodeModel::NodeCopySetting>(engine, qtscript_QAbstractXmlNodeModel_NodeCopySetting_toScriptValue,
        qtscript_QAbstractXmlNodeModel_NodeCopySetting_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractXmlNodeModel_NodeCopySetting_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractXmlNodeModel_NodeCopySetting_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractXmlNodeModel
//

static QScriptValue qtscript_QAbstractXmlNodeModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractXmlNodeModel* _q_self = qscriptvalue_cast<QAbstractXmlNodeModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractXmlNodeModel.%0(): this object is not a QAbstractXmlNodeModel")
            .arg(qtscript_QAbstractXmlNodeModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QUrl _q_result = _q_self->baseUri(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QXmlNodeModelIndex _q_arg1 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(1));
        QXmlNodeModelIndex::DocumentOrder _q_result = _q_self->compareOrder(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QUrl _q_result = _q_self->documentUri(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
        QXmlNodeModelIndex _q_result = _q_self->elementById(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QXmlNodeModelIndex::NodeKind _q_result = _q_self->kind(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QXmlName _q_result = _q_self->name(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QVector<QXmlName> _q_result = _q_self->namespaceBindings(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QXmlName _q_arg0 = qscriptvalue_cast<QXmlName>(context->argument(0));
        QVector<QXmlNodeModelIndex> _q_result = _q_self->nodesByIdref(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QXmlNodeModelIndex _q_result = _q_self->root(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QSourceLocation _q_result = _q_self->sourceLocation(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QString _q_result = _q_self->stringValue(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QXmlNodeModelIndex _q_arg0 = qscriptvalue_cast<QXmlNodeModelIndex>(context->argument(0));
        QVariant _q_result = _q_self->typedValue(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QAbstractXmlNodeModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractXmlNodeModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractXmlNodeModel_function_names[_id+1],
        qtscript_QAbstractXmlNodeModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractXmlNodeModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QAbstractXmlNodeModel cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractXmlNodeModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractXmlNodeModel_function_names[_id],
        qtscript_QAbstractXmlNodeModel_function_signatures[_id]);
}

QScriptValue qtscript_create_QAbstractXmlNodeModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractXmlNodeModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractXmlNodeModel*)0));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractXmlNodeModel_prototype_call, qtscript_QAbstractXmlNodeModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractXmlNodeModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAbstractXmlNodeModel*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractXmlNodeModel_static_call, proto, qtscript_QAbstractXmlNodeModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SimpleAxis"),
        qtscript_create_QAbstractXmlNodeModel_SimpleAxis_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NodeCopySetting"),
        qtscript_create_QAbstractXmlNodeModel_NodeCopySetting_class(engine, ctor));
    return ctor;
}
