#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qitemselectionmodel.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qitemselectionmodel.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QItemSelectionModel.h"

static const char * const qtscript_QItemSelectionModel_function_names[] = {
    "QItemSelectionModel"
    // static
    // prototype
    , "columnIntersectsSelection"
    , "currentIndex"
    , "hasSelection"
    , "isColumnSelected"
    , "isRowSelected"
    , "isSelected"
    , "model"
    , "rowIntersectsSelection"
    , "selectedColumns"
    , "selectedIndexes"
    , "selectedRows"
    , "selection"
    , "toString"
};

static const char * const qtscript_QItemSelectionModel_function_signatures[] = {
    "QAbstractItemModel model\nQAbstractItemModel model, QObject parent"
    // static
    // prototype
    , "int column, QModelIndex parent"
    , ""
    , ""
    , "int column, QModelIndex parent"
    , "int row, QModelIndex parent"
    , "QModelIndex index"
    , ""
    , "int row, QModelIndex parent"
    , "int row"
    , ""
    , "int column"
    , ""
""
};

static const int qtscript_QItemSelectionModel_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 0
    , 0
    , 2
    , 2
    , 1
    , 0
    , 2
    , 1
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QItemSelectionModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QItemSelectionModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QItemSelectionModel*)
Q_DECLARE_METATYPE(QtScriptShell_QItemSelectionModel*)
Q_DECLARE_METATYPE(QItemSelectionModel::SelectionFlag)
Q_DECLARE_METATYPE(QFlags<QItemSelectionModel::SelectionFlag>)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QItemSelection)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QItemSelectionModel::SelectionFlag
//

static const QItemSelectionModel::SelectionFlag qtscript_QItemSelectionModel_SelectionFlag_values[] = {
    QItemSelectionModel::NoUpdate
    , QItemSelectionModel::Clear
    , QItemSelectionModel::Select
    , QItemSelectionModel::ClearAndSelect
    , QItemSelectionModel::Deselect
    , QItemSelectionModel::Toggle
    , QItemSelectionModel::Current
    , QItemSelectionModel::SelectCurrent
    , QItemSelectionModel::ToggleCurrent
    , QItemSelectionModel::Rows
    , QItemSelectionModel::Columns
};

static const char * const qtscript_QItemSelectionModel_SelectionFlag_keys[] = {
    "NoUpdate"
    , "Clear"
    , "Select"
    , "ClearAndSelect"
    , "Deselect"
    , "Toggle"
    , "Current"
    , "SelectCurrent"
    , "ToggleCurrent"
    , "Rows"
    , "Columns"
};

static QString qtscript_QItemSelectionModel_SelectionFlag_toStringHelper(QItemSelectionModel::SelectionFlag value)
{
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QItemSelectionModel_SelectionFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QItemSelectionModel_SelectionFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QItemSelectionModel_SelectionFlag_toScriptValue(QScriptEngine *engine, const QItemSelectionModel::SelectionFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QItemSelectionModel"));
    return clazz.property(qtscript_QItemSelectionModel_SelectionFlag_toStringHelper(value));
}

static void qtscript_QItemSelectionModel_SelectionFlag_fromScriptValue(const QScriptValue &value, QItemSelectionModel::SelectionFlag &out)
{
    out = qvariant_cast<QItemSelectionModel::SelectionFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QItemSelectionModel_SelectionFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 11; ++i) {
        if (qtscript_QItemSelectionModel_SelectionFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QItemSelectionModel::SelectionFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("SelectionFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QItemSelectionModel_SelectionFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QItemSelectionModel::SelectionFlag value = qscriptvalue_cast<QItemSelectionModel::SelectionFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QItemSelectionModel_SelectionFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QItemSelectionModel::SelectionFlag value = qscriptvalue_cast<QItemSelectionModel::SelectionFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QItemSelectionModel_SelectionFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QItemSelectionModel_SelectionFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QItemSelectionModel_SelectionFlag,
        qtscript_QItemSelectionModel_SelectionFlag_valueOf, qtscript_QItemSelectionModel_SelectionFlag_toString);
    qScriptRegisterMetaType<QItemSelectionModel::SelectionFlag>(engine, qtscript_QItemSelectionModel_SelectionFlag_toScriptValue,
        qtscript_QItemSelectionModel_SelectionFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QItemSelectionModel_SelectionFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QItemSelectionModel_SelectionFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QItemSelectionModel::SelectionFlags
//

static QScriptValue qtscript_QItemSelectionModel_SelectionFlags_toScriptValue(QScriptEngine *engine, const QItemSelectionModel::SelectionFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QItemSelectionModel_SelectionFlags_fromScriptValue(const QScriptValue &value, QItemSelectionModel::SelectionFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QItemSelectionModel::SelectionFlags>())
        out = qvariant_cast<QItemSelectionModel::SelectionFlags>(var);
    else if (var.userType() == qMetaTypeId<QItemSelectionModel::SelectionFlag>())
        out = qvariant_cast<QItemSelectionModel::SelectionFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QItemSelectionModel_SelectionFlags(QScriptContext *context, QScriptEngine *engine)
{
    QItemSelectionModel::SelectionFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QItemSelectionModel::SelectionFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QItemSelectionModel::SelectionFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("SelectionFlags(): argument %0 is not of type SelectionFlag").arg(i));
            }
            result |= qvariant_cast<QItemSelectionModel::SelectionFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QItemSelectionModel_SelectionFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QItemSelectionModel::SelectionFlags value = qscriptvalue_cast<QItemSelectionModel::SelectionFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QItemSelectionModel_SelectionFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QItemSelectionModel::SelectionFlags value = qscriptvalue_cast<QItemSelectionModel::SelectionFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 11; ++i) {
        if ((value & qtscript_QItemSelectionModel_SelectionFlag_values[i]) == qtscript_QItemSelectionModel_SelectionFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QItemSelectionModel_SelectionFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QItemSelectionModel_SelectionFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QItemSelectionModel::SelectionFlags>() == otherObj.value<QItemSelectionModel::SelectionFlags>())));
}

static QScriptValue qtscript_create_QItemSelectionModel_SelectionFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QItemSelectionModel_SelectionFlags, qtscript_QItemSelectionModel_SelectionFlags_valueOf,
        qtscript_QItemSelectionModel_SelectionFlags_toString, qtscript_QItemSelectionModel_SelectionFlags_equals);
    qScriptRegisterMetaType<QItemSelectionModel::SelectionFlags>(engine, qtscript_QItemSelectionModel_SelectionFlags_toScriptValue,
        qtscript_QItemSelectionModel_SelectionFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QItemSelectionModel
//

static QScriptValue qtscript_QItemSelectionModel_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QItemSelectionModel* _q_self = qscriptvalue_cast<QItemSelectionModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QItemSelectionModel.%0(): this object is not a QItemSelectionModel")
            .arg(qtscript_QItemSelectionModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->columnIntersectsSelection(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->currentIndex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasSelection();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->isColumnSelected(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->isRowSelected(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->isSelected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = const_cast<QAbstractItemModel*>(_q_self->model());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->rowIntersectsSelection(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QList<QModelIndex> _q_result = _q_self->selectedColumns();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QModelIndex> _q_result = _q_self->selectedColumns(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QList<QModelIndex> _q_result = _q_self->selectedIndexes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QList<QModelIndex> _q_result = _q_self->selectedRows();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QModelIndex> _q_result = _q_self->selectedRows(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QItemSelection _q_result = _q_self->selection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QItemSelectionModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemSelectionModel_throw_ambiguity_error_helper(context,
        qtscript_QItemSelectionModel_function_names[_id+1],
        qtscript_QItemSelectionModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QItemSelectionModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QItemSelectionModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        QtScriptShell_QItemSelectionModel* _q_cpp_result = new QtScriptShell_QItemSelectionModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QItemSelectionModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QItemSelectionModel* _q_cpp_result = new QtScriptShell_QItemSelectionModel(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QItemSelectionModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemSelectionModel_throw_ambiguity_error_helper(context,
        qtscript_QItemSelectionModel_function_names[_id],
        qtscript_QItemSelectionModel_function_signatures[_id]);
}

static QScriptValue qtscript_QItemSelectionModel_toScriptValue(QScriptEngine *engine, QItemSelectionModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QItemSelectionModel_fromScriptValue(const QScriptValue &value, QItemSelectionModel* &out)
{
    out = qobject_cast<QItemSelectionModel*>(value.toQObject());
}

QScriptValue qtscript_create_QItemSelectionModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QItemSelectionModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QItemSelectionModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemSelectionModel_prototype_call, qtscript_QItemSelectionModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QItemSelectionModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QItemSelectionModel*>(engine, qtscript_QItemSelectionModel_toScriptValue, 
        qtscript_QItemSelectionModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QItemSelectionModel_static_call, proto, qtscript_QItemSelectionModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SelectionFlag"),
        qtscript_create_QItemSelectionModel_SelectionFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectionFlags"),
        qtscript_create_QItemSelectionModel_SelectionFlags_class(engine));
    return ctor;
}
