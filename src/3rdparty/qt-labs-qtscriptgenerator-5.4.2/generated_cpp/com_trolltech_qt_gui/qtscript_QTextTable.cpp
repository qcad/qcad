#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtexttable.h>
#include <QTextCursor>
#include <QTextFrame>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qtextobject.h>
#include <qtexttable.h>

#include "qtscriptshell_QTextTable.h"

static const char * const qtscript_QTextTable_function_names[] = {
    "QTextTable"
    // static
    // prototype
    , "appendColumns"
    , "appendRows"
    , "cellAt"
    , "columns"
    , "insertColumns"
    , "insertRows"
    , "mergeCells"
    , "removeColumns"
    , "removeRows"
    , "resize"
    , "rowEnd"
    , "rowStart"
    , "rows"
    , "setFormat"
    , "splitCell"
    , "tableFormat"
    , "toString"
};

static const char * const qtscript_QTextTable_function_signatures[] = {
    "QTextDocument doc"
    // static
    // prototype
    , "int count"
    , "int count"
    , "QTextCursor c\nint position\nint row, int col"
    , ""
    , "int pos, int num"
    , "int pos, int num"
    , "QTextCursor cursor\nint row, int col, int numRows, int numCols"
    , "int pos, int num"
    , "int pos, int num"
    , "int rows, int cols"
    , "QTextCursor c"
    , "QTextCursor c"
    , ""
    , "QTextTableFormat format"
    , "int row, int col, int numRows, int numCols"
    , ""
""
};

static const int qtscript_QTextTable_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 2
    , 0
    , 2
    , 2
    , 4
    , 2
    , 2
    , 2
    , 1
    , 1
    , 0
    , 1
    , 4
    , 0
    , 0
};

static QScriptValue qtscript_QTextTable_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextTable::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextTable*)
Q_DECLARE_METATYPE(QtScriptShell_QTextTable*)
Q_DECLARE_METATYPE(QTextCursor)
Q_DECLARE_METATYPE(QTextTableCell)
Q_DECLARE_METATYPE(QTextTableFormat)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextFrame*)

//
// QTextTable
//

static QScriptValue qtscript_QTextTable_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextTable* _q_self = qscriptvalue_cast<QTextTable*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextTable.%0(): this object is not a QTextTable")
            .arg(qtscript_QTextTable_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->appendColumns(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->appendRows(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTextCursor>() == context->argument(0).toVariant().userType())) {
            QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
            QTextTableCell _q_result = _q_self->cellAt(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QTextTableCell _q_result = _q_self->cellAt(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTextTableCell _q_result = _q_self->cellAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columns();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->insertColumns(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->insertRows(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        _q_self->mergeCells(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->mergeCells(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->removeColumns(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->removeRows(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->resize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        QTextCursor _q_result = _q_self->rowEnd(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        QTextCursor _q_result = _q_self->rowStart(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rows();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QTextTableFormat _q_arg0 = qscriptvalue_cast<QTextTableFormat>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->splitCell(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QTextTableFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16: {
    QString result = QString::fromLatin1("QTextTable");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTable_throw_ambiguity_error_helper(context,
        qtscript_QTextTable_function_names[_id+1],
        qtscript_QTextTable_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextTable_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextTable(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        QtScriptShell_QTextTable* _q_cpp_result = new QtScriptShell_QTextTable(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextTable*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextTable_throw_ambiguity_error_helper(context,
        qtscript_QTextTable_function_names[_id],
        qtscript_QTextTable_function_signatures[_id]);
}

static QScriptValue qtscript_QTextTable_toScriptValue(QScriptEngine *engine, QTextTable* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTextTable_fromScriptValue(const QScriptValue &value, QTextTable* &out)
{
    out = qobject_cast<QTextTable*>(value.toQObject());
}

QScriptValue qtscript_create_QTextTable_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextTable*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextTable*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextFrame*>()));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextTable_prototype_call, qtscript_QTextTable_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextTable_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTextTable*>(engine, qtscript_QTextTable_toScriptValue, 
        qtscript_QTextTable_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextTable_static_call, proto, qtscript_QTextTable_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
