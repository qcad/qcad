#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdatawidgetmapper.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatawidgetmapper.h>
#include <qlist.h>
#include <qobject.h>
#include <qwidget.h>

#include "qtscriptshell_QDataWidgetMapper.h"

static const char * const qtscript_QDataWidgetMapper_function_names[] = {
    "QDataWidgetMapper"
    // static
    // prototype
    , "addMapping"
    , "clearMapping"
    , "itemDelegate"
    , "mappedPropertyName"
    , "mappedSection"
    , "mappedWidgetAt"
    , "model"
    , "removeMapping"
    , "rootIndex"
    , "setItemDelegate"
    , "setModel"
    , "setRootIndex"
    , "toString"
};

static const char * const qtscript_QDataWidgetMapper_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QWidget widget, int section\nQWidget widget, int section, QByteArray propertyName"
    , ""
    , ""
    , "QWidget widget"
    , "QWidget widget"
    , "int section"
    , ""
    , "QWidget widget"
    , ""
    , "QAbstractItemDelegate delegate"
    , "QAbstractItemModel model"
    , "QModelIndex index"
""
};

static const int qtscript_QDataWidgetMapper_function_lengths[] = {
    1
    // static
    // prototype
    , 3
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QDataWidgetMapper_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDataWidgetMapper::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QDataWidgetMapper_metaObject()
{
    return &QDataWidgetMapper::staticMetaObject;
}

Q_DECLARE_METATYPE(QDataWidgetMapper*)
Q_DECLARE_METATYPE(QtScriptShell_QDataWidgetMapper*)
Q_DECLARE_METATYPE(QDataWidgetMapper::SubmitPolicy)
Q_DECLARE_METATYPE(QAbstractItemDelegate*)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QModelIndex)

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
// QDataWidgetMapper::SubmitPolicy
//

static const QDataWidgetMapper::SubmitPolicy qtscript_QDataWidgetMapper_SubmitPolicy_values[] = {
    QDataWidgetMapper::AutoSubmit
    , QDataWidgetMapper::ManualSubmit
};

static const char * const qtscript_QDataWidgetMapper_SubmitPolicy_keys[] = {
    "AutoSubmit"
    , "ManualSubmit"
};

static QString qtscript_QDataWidgetMapper_SubmitPolicy_toStringHelper(QDataWidgetMapper::SubmitPolicy value)
{
    const QMetaObject *meta = qtscript_QDataWidgetMapper_metaObject();
    int idx = meta->indexOfEnumerator("SubmitPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QDataWidgetMapper_SubmitPolicy_toScriptValue(QScriptEngine *engine, const QDataWidgetMapper::SubmitPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDataWidgetMapper"));
    return clazz.property(qtscript_QDataWidgetMapper_SubmitPolicy_toStringHelper(value));
}

static void qtscript_QDataWidgetMapper_SubmitPolicy_fromScriptValue(const QScriptValue &value, QDataWidgetMapper::SubmitPolicy &out)
{
    out = qvariant_cast<QDataWidgetMapper::SubmitPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QDataWidgetMapper_SubmitPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QDataWidgetMapper_metaObject();
    int idx = meta->indexOfEnumerator("SubmitPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QDataWidgetMapper::SubmitPolicy>(arg));
    return context->throwError(QString::fromLatin1("SubmitPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDataWidgetMapper_SubmitPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDataWidgetMapper::SubmitPolicy value = qscriptvalue_cast<QDataWidgetMapper::SubmitPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDataWidgetMapper_SubmitPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDataWidgetMapper::SubmitPolicy value = qscriptvalue_cast<QDataWidgetMapper::SubmitPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QDataWidgetMapper_SubmitPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QDataWidgetMapper_SubmitPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDataWidgetMapper_SubmitPolicy,
        qtscript_QDataWidgetMapper_SubmitPolicy_valueOf, qtscript_QDataWidgetMapper_SubmitPolicy_toString);
    qScriptRegisterMetaType<QDataWidgetMapper::SubmitPolicy>(engine, qtscript_QDataWidgetMapper_SubmitPolicy_toScriptValue,
        qtscript_QDataWidgetMapper_SubmitPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDataWidgetMapper_SubmitPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDataWidgetMapper_SubmitPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDataWidgetMapper
//

static QScriptValue qtscript_QDataWidgetMapper_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDataWidgetMapper* _q_self = qscriptvalue_cast<QDataWidgetMapper*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDataWidgetMapper.%0(): this object is not a QDataWidgetMapper")
            .arg(qtscript_QDataWidgetMapper_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->addMapping(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QByteArray _q_arg2 = qscriptvalue_cast<QByteArray>(context->argument(2));
        _q_self->addMapping(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clearMapping();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QAbstractItemDelegate* _q_result = _q_self->itemDelegate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QByteArray _q_result = _q_self->mappedPropertyName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_result = _q_self->mappedSection(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_result = _q_self->mappedWidgetAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = _q_self->model();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->removeMapping(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->rootIndex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QAbstractItemDelegate* _q_arg0 = qscriptvalue_cast<QAbstractItemDelegate*>(context->argument(0));
        _q_self->setItemDelegate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        _q_self->setModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        _q_self->setRootIndex(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QDataWidgetMapper");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDataWidgetMapper_throw_ambiguity_error_helper(context,
        qtscript_QDataWidgetMapper_function_names[_id+1],
        qtscript_QDataWidgetMapper_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDataWidgetMapper_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDataWidgetMapper(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDataWidgetMapper* _q_cpp_result = new QtScriptShell_QDataWidgetMapper();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDataWidgetMapper*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QDataWidgetMapper* _q_cpp_result = new QtScriptShell_QDataWidgetMapper(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDataWidgetMapper*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDataWidgetMapper_throw_ambiguity_error_helper(context,
        qtscript_QDataWidgetMapper_function_names[_id],
        qtscript_QDataWidgetMapper_function_signatures[_id]);
}

static QScriptValue qtscript_QDataWidgetMapper_toScriptValue(QScriptEngine *engine, QDataWidgetMapper* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDataWidgetMapper_fromScriptValue(const QScriptValue &value, QDataWidgetMapper* &out)
{
    out = qobject_cast<QDataWidgetMapper*>(value.toQObject());
}

QScriptValue qtscript_create_QDataWidgetMapper_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDataWidgetMapper*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDataWidgetMapper*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDataWidgetMapper_prototype_call, qtscript_QDataWidgetMapper_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDataWidgetMapper_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDataWidgetMapper*>(engine, qtscript_QDataWidgetMapper_toScriptValue, 
        qtscript_QDataWidgetMapper_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDataWidgetMapper_static_call, proto, qtscript_QDataWidgetMapper_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SubmitPolicy"),
        qtscript_create_QDataWidgetMapper_SubmitPolicy_class(engine, ctor));
    return ctor;
}
