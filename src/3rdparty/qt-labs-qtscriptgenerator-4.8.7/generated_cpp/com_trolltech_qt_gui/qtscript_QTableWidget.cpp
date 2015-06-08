#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtablewidget.h>
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
#include <qmimedata.h>
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
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtablewidget.h>
#include <qwidget.h>

#include "qtscriptshell_QTableWidget.h"

static const char * const qtscript_QTableWidget_function_names[] = {
    "QTableWidget"
    // static
    // prototype
    , "cellWidget"
    , "closePersistentEditor"
    , "column"
    , "currentColumn"
    , "currentItem"
    , "currentRow"
    , "editItem"
    , "findItems"
    , "horizontalHeaderItem"
    , "item"
    , "itemAt"
    , "itemPrototype"
    , "openPersistentEditor"
    , "removeCellWidget"
    , "row"
    , "selectedItems"
    , "selectedRanges"
    , "setCellWidget"
    , "setCurrentCell"
    , "setCurrentItem"
    , "setHorizontalHeaderItem"
    , "setHorizontalHeaderLabels"
    , "setItem"
    , "setItemPrototype"
    , "setRangeSelected"
    , "setVerticalHeaderItem"
    , "setVerticalHeaderLabels"
    , "sortItems"
    , "takeHorizontalHeaderItem"
    , "takeItem"
    , "takeVerticalHeaderItem"
    , "verticalHeaderItem"
    , "visualColumn"
    , "visualItemRect"
    , "visualRow"
    , "toString"
};

static const char * const qtscript_QTableWidget_function_signatures[] = {
    "QWidget parent\nint rows, int columns, QWidget parent"
    // static
    // prototype
    , "int row, int column"
    , "QTableWidgetItem item"
    , "QTableWidgetItem item"
    , ""
    , ""
    , ""
    , "QTableWidgetItem item"
    , "String text, MatchFlags flags"
    , "int column"
    , "int row, int column"
    , "QPoint p\nint x, int y"
    , ""
    , "QTableWidgetItem item"
    , "int row, int column"
    , "QTableWidgetItem item"
    , ""
    , ""
    , "int row, int column, QWidget widget"
    , "int row, int column\nint row, int column, SelectionFlags command"
    , "QTableWidgetItem item\nQTableWidgetItem item, SelectionFlags command"
    , "int column, QTableWidgetItem item"
    , "List labels"
    , "int row, int column, QTableWidgetItem item"
    , "QTableWidgetItem item"
    , "QTableWidgetSelectionRange range, bool select"
    , "int row, QTableWidgetItem item"
    , "List labels"
    , "int column, SortOrder order"
    , "int column"
    , "int row, int column"
    , "int row"
    , "int row"
    , "int logicalColumn"
    , "QTableWidgetItem item"
    , "int logicalRow"
""
};

static const int qtscript_QTableWidget_function_lengths[] = {
    3
    // static
    // prototype
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 2
    , 2
    , 0
    , 1
    , 2
    , 1
    , 0
    , 0
    , 3
    , 3
    , 2
    , 2
    , 1
    , 3
    , 1
    , 2
    , 2
    , 1
    , 2
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QTableWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTableWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTableWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QTableWidget*)
Q_DECLARE_METATYPE(QTableWidgetItem*)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QList<QTableWidgetItem*>)
Q_DECLARE_METATYPE(QTableWidgetSelectionRange)
Q_DECLARE_METATYPE(QList<QTableWidgetSelectionRange>)
Q_DECLARE_METATYPE(QFlags<QItemSelectionModel::SelectionFlag>)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QTableView*)

//
// QTableWidget
//

static QScriptValue qtscript_QTableWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 35;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTableWidget* _q_self = qscriptvalue_cast<QTableWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTableWidget.%0(): this object is not a QTableWidget")
            .arg(qtscript_QTableWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_result = _q_self->cellWidget(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        _q_self->closePersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        int _q_result = _q_self->column(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentColumn();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTableWidgetItem* _q_result = _q_self->currentItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentRow();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        _q_self->editItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<Qt::MatchFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(1));
        QList<QTableWidgetItem*> _q_result = _q_self->findItems(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTableWidgetItem* _q_result = _q_self->horizontalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTableWidgetItem* _q_result = _q_self->item(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QTableWidgetItem* _q_result = _q_self->itemAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTableWidgetItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QTableWidgetItem* _q_result = const_cast<QTableWidgetItem*>(_q_self->itemPrototype());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        _q_self->openPersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->removeCellWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        int _q_result = _q_self->row(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QList<QTableWidgetItem*> _q_result = _q_self->selectedItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QList<QTableWidgetSelectionRange> _q_result = _q_self->selectedRanges();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        _q_self->setCellWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setCurrentCell(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<QItemSelectionModel::SelectionFlag> _q_arg2 = qscriptvalue_cast<QFlags<QItemSelectionModel::SelectionFlag> >(context->argument(2));
        _q_self->setCurrentCell(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        _q_self->setCurrentItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        QFlags<QItemSelectionModel::SelectionFlag> _q_arg1 = qscriptvalue_cast<QFlags<QItemSelectionModel::SelectionFlag> >(context->argument(1));
        _q_self->setCurrentItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTableWidgetItem* _q_arg1 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(1));
        _q_self->setHorizontalHeaderItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setHorizontalHeaderLabels(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTableWidgetItem* _q_arg2 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(2));
        _q_self->setItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        _q_self->setItemPrototype(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        QTableWidgetSelectionRange _q_arg0 = qscriptvalue_cast<QTableWidgetSelectionRange>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRangeSelected(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTableWidgetItem* _q_arg1 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(1));
        _q_self->setVerticalHeaderItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setVerticalHeaderLabels(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->sortItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sortItems(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTableWidgetItem* _q_result = _q_self->takeHorizontalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTableWidgetItem* _q_result = _q_self->takeItem(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTableWidgetItem* _q_result = _q_self->takeVerticalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTableWidgetItem* _q_result = _q_self->verticalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->visualColumn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QTableWidgetItem* _q_arg0 = qscriptvalue_cast<QTableWidgetItem*>(context->argument(0));
        QRect _q_result = _q_self->visualItemRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->visualRow(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35: {
    QString result = QString::fromLatin1("QTableWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableWidget_throw_ambiguity_error_helper(context,
        qtscript_QTableWidget_function_names[_id+1],
        qtscript_QTableWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTableWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTableWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTableWidget* _q_cpp_result = new QtScriptShell_QTableWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTableWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QTableWidget* _q_cpp_result = new QtScriptShell_QTableWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTableWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QTableWidget* _q_cpp_result = new QtScriptShell_QTableWidget(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTableWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QtScriptShell_QTableWidget* _q_cpp_result = new QtScriptShell_QTableWidget(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTableWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableWidget_throw_ambiguity_error_helper(context,
        qtscript_QTableWidget_function_names[_id],
        qtscript_QTableWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QTableWidget_toScriptValue(QScriptEngine *engine, QTableWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTableWidget_fromScriptValue(const QScriptValue &value, QTableWidget* &out)
{
    out = qobject_cast<QTableWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QTableWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTableWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTableWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTableView*>()));
    for (int i = 0; i < 36; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTableWidget_prototype_call, qtscript_QTableWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTableWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTableWidget*>(engine, qtscript_QTableWidget_toScriptValue, 
        qtscript_QTableWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTableWidget_static_call, proto, qtscript_QTableWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
