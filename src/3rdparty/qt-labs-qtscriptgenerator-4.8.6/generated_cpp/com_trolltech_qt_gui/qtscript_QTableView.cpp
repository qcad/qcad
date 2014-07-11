#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtableview.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qheaderview.h>
#include <qicon.h>
#include <qinputcontext.h>
#include <qitemselectionmodel.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtableview.h>
#include <qwidget.h>

#include "qtscriptshell_QTableView.h"

static const char * const qtscript_QTableView_function_names[] = {
    "QTableView"
    // static
    // prototype
    , "clearSpans"
    , "columnAt"
    , "columnSpan"
    , "columnViewportPosition"
    , "columnWidth"
    , "horizontalHeader"
    , "isColumnHidden"
    , "isRowHidden"
    , "rowAt"
    , "rowHeight"
    , "rowSpan"
    , "rowViewportPosition"
    , "setColumnHidden"
    , "setColumnWidth"
    , "setHorizontalHeader"
    , "setRowHeight"
    , "setRowHidden"
    , "setSpan"
    , "setVerticalHeader"
    , "sortByColumn"
    , "verticalHeader"
    , "toString"
};

static const char * const qtscript_QTableView_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , "int x"
    , "int row, int column"
    , "int column"
    , "int column"
    , ""
    , "int column"
    , "int row"
    , "int y"
    , "int row"
    , "int row, int column"
    , "int row"
    , "int column, bool hide"
    , "int column, int width"
    , "QHeaderView header"
    , "int row, int height"
    , "int row, bool hide"
    , "int row, int column, int rowSpan, int columnSpan"
    , "QHeaderView header"
    , "int column, SortOrder order"
    , ""
""
};

static const int qtscript_QTableView_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 2
    , 2
    , 1
    , 2
    , 2
    , 4
    , 1
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QTableView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTableView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTableView*)
Q_DECLARE_METATYPE(QtScriptShell_QTableView*)
Q_DECLARE_METATYPE(QHeaderView*)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QAbstractItemView*)

//
// QTableView
//

static QScriptValue qtscript_QTableView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 21;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTableView* _q_self = qscriptvalue_cast<QTableView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTableView.%0(): this object is not a QTableView")
            .arg(qtscript_QTableView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clearSpans();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->columnSpan(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnViewportPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnWidth(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QHeaderView* _q_result = _q_self->horizontalHeader();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isColumnHidden(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isRowHidden(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->rowAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->rowHeight(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->rowSpan(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->rowViewportPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setColumnHidden(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setColumnWidth(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QHeaderView* _q_arg0 = qscriptvalue_cast<QHeaderView*>(context->argument(0));
        _q_self->setHorizontalHeader(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setRowHeight(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRowHidden(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setSpan(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QHeaderView* _q_arg0 = qscriptvalue_cast<QHeaderView*>(context->argument(0));
        _q_self->setVerticalHeader(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sortByColumn(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QHeaderView* _q_result = _q_self->verticalHeader();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("QTableView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableView_throw_ambiguity_error_helper(context,
        qtscript_QTableView_function_names[_id+1],
        qtscript_QTableView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTableView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTableView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTableView* _q_cpp_result = new QtScriptShell_QTableView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTableView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QTableView* _q_cpp_result = new QtScriptShell_QTableView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTableView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableView_throw_ambiguity_error_helper(context,
        qtscript_QTableView_function_names[_id],
        qtscript_QTableView_function_signatures[_id]);
}

static QScriptValue qtscript_QTableView_toScriptValue(QScriptEngine *engine, QTableView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTableView_fromScriptValue(const QScriptValue &value, QTableView* &out)
{
    out = qobject_cast<QTableView*>(value.toQObject());
}

QScriptValue qtscript_create_QTableView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTableView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTableView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemView*>()));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTableView_prototype_call, qtscript_QTableView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTableView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTableView*>(engine, qtscript_QTableView_toScriptValue, 
        qtscript_QTableView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTableView_static_call, proto, qtscript_QTableView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
