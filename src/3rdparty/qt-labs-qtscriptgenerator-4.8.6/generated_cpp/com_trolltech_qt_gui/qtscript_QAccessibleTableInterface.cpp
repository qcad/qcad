#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessible2.h>
#include <QVariant>
#include <qaccessible.h>
#include <qlist.h>

#include "qtscriptshell_QAccessibleTableInterface.h"

static const char * const qtscript_QAccessibleTableInterface_function_names[] = {
    "QAccessibleTableInterface"
    // static
    // prototype
    , "accessibleAt"
    , "caption"
    , "cellAtIndex"
    , "childIndex"
    , "columnCount"
    , "columnDescription"
    , "columnHeader"
    , "columnIndex"
    , "columnSpan"
    , "isColumnSelected"
    , "isRowSelected"
    , "isSelected"
    , "rowCount"
    , "rowDescription"
    , "rowHeader"
    , "rowIndex"
    , "rowSpan"
    , "selectColumn"
    , "selectRow"
    , "selectedColumnCount"
    , "selectedColumns"
    , "selectedRowCount"
    , "selectedRows"
    , "summary"
    , "unselectColumn"
    , "unselectRow"
    , "toString"
};

static const char * const qtscript_QAccessibleTableInterface_function_signatures[] = {
    ""
    // static
    // prototype
    , "int row, int column"
    , ""
    , "int index, int row, int column, int rowSpan, int columnSpan, bool isSelected"
    , "int rowIndex, int columnIndex"
    , ""
    , "int column"
    , ""
    , "int childIndex"
    , "int row, int column"
    , "int column"
    , "int row"
    , "int row, int column"
    , ""
    , "int row"
    , ""
    , "int childIndex"
    , "int row, int column"
    , "int column"
    , "int row"
    , ""
    , "int maxColumns, List columns"
    , ""
    , "int maxRows, List rows"
    , ""
    , "int column"
    , "int row"
""
};

static const int qtscript_QAccessibleTableInterface_function_lengths[] = {
    0
    // static
    // prototype
    , 2
    , 0
    , 6
    , 2
    , 0
    , 1
    , 0
    , 1
    , 2
    , 1
    , 1
    , 2
    , 0
    , 1
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
    , 2
    , 0
    , 2
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAccessibleTableInterface_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessibleTableInterface::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessibleTableInterface*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessibleTableInterface*)
Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(QList<int>*)
Q_DECLARE_METATYPE(QAccessible2Interface*)

//
// QAccessibleTableInterface
//

static QScriptValue qtscript_QAccessibleTableInterface_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 26;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAccessibleTableInterface* _q_self = qscriptvalue_cast<QAccessibleTableInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessibleTableInterface.%0(): this object is not a QAccessibleTableInterface")
            .arg(qtscript_QAccessibleTableInterface_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QAccessibleInterface* _q_result = _q_self->accessibleAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QAccessibleInterface* _q_result = _q_self->caption();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
        bool* _q_arg5 = qscriptvalue_cast<bool*>(context->argument(5));
        _q_self->cellAtIndex(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->childIndex(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->columnDescription(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QAccessibleInterface* _q_result = _q_self->columnHeader();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnIndex(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->columnSpan(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isColumnSelected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isRowSelected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->isSelected(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->rowDescription(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QAccessibleInterface* _q_result = _q_self->rowHeader();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->rowIndex(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->rowSpan(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->selectColumn(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->selectRow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->selectedColumnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<int>* _q_arg1 = qscriptvalue_cast<QList<int>*>(context->argument(1));
        int _q_result = _q_self->selectedColumns(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->selectedRowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<int>* _q_arg1 = qscriptvalue_cast<QList<int>*>(context->argument(1));
        int _q_result = _q_self->selectedRows(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QAccessibleInterface* _q_result = _q_self->summary();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->unselectColumn(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->unselectRow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26: {
    QString result = QString::fromLatin1("QAccessibleTableInterface");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleTableInterface_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleTableInterface_function_names[_id+1],
        qtscript_QAccessibleTableInterface_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessibleTableInterface_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessibleTableInterface(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAccessibleTableInterface* _q_cpp_result = new QtScriptShell_QAccessibleTableInterface();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleTableInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleTableInterface_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleTableInterface_function_names[_id],
        qtscript_QAccessibleTableInterface_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessibleTableInterface_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessibleTableInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessibleTableInterface*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAccessible2Interface*>()));
    for (int i = 0; i < 27; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessibleTableInterface_prototype_call, qtscript_QAccessibleTableInterface_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAccessibleTableInterface_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAccessibleTableInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessibleTableInterface_static_call, proto, qtscript_QAccessibleTableInterface_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
