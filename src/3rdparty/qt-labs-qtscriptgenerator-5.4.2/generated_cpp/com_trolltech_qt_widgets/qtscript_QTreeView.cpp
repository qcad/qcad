#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtreeview.h>
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
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtreeview.h>
#include <qvector.h>
#include <qwidget.h>

#include "qtscriptshell_QTreeView.h"

static const char * const qtscript_QTreeView_function_names[] = {
    "QTreeView"
    // static
    // prototype
    , "columnAt"
    , "columnViewportPosition"
    , "columnWidth"
    , "header"
    , "indexAbove"
    , "indexBelow"
    , "isColumnHidden"
    , "isExpanded"
    , "isFirstColumnSpanned"
    , "isRowHidden"
    , "setColumnHidden"
    , "setColumnWidth"
    , "setExpanded"
    , "setFirstColumnSpanned"
    , "setHeader"
    , "setRowHidden"
    , "setTreePosition"
    , "sortByColumn"
    , "treePosition"
    , "toString"
};

static const char * const qtscript_QTreeView_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "int x"
    , "int column"
    , "int column"
    , ""
    , "QModelIndex index"
    , "QModelIndex index"
    , "int column"
    , "QModelIndex index"
    , "int row, QModelIndex parent"
    , "int row, QModelIndex parent"
    , "int column, bool hide"
    , "int column, int width"
    , "QModelIndex index, bool expand"
    , "int row, QModelIndex parent, bool span"
    , "QHeaderView header"
    , "int row, QModelIndex parent, bool hide"
    , "int logicalIndex"
    , "int column, SortOrder order"
    , ""
""
};

static const int qtscript_QTreeView_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 3
    , 1
    , 3
    , 1
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QTreeView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTreeView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTreeView*)
Q_DECLARE_METATYPE(QtScriptShell_QTreeView*)
Q_DECLARE_METATYPE(QHeaderView*)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractItemView*)

//
// QTreeView
//

static QScriptValue qtscript_QTreeView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTreeView* _q_self = qscriptvalue_cast<QTreeView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTreeView.%0(): this object is not a QTreeView")
            .arg(qtscript_QTreeView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnViewportPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnWidth(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QHeaderView* _q_result = _q_self->header();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->indexAbove(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->indexBelow(_q_arg0);
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
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->isExpanded(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->isFirstColumnSpanned(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->isRowHidden(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setColumnHidden(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setColumnWidth(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setExpanded(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_arg2 = context->argument(2).toBoolean();
        _q_self->setFirstColumnSpanned(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QHeaderView* _q_arg0 = qscriptvalue_cast<QHeaderView*>(context->argument(0));
        _q_self->setHeader(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_arg2 = context->argument(2).toBoolean();
        _q_self->setRowHidden(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTreePosition(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sortByColumn(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->treePosition();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19: {
    QString result = QString::fromLatin1("QTreeView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTreeView_throw_ambiguity_error_helper(context,
        qtscript_QTreeView_function_names[_id+1],
        qtscript_QTreeView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTreeView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTreeView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTreeView* _q_cpp_result = new QtScriptShell_QTreeView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTreeView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QTreeView* _q_cpp_result = new QtScriptShell_QTreeView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTreeView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTreeView_throw_ambiguity_error_helper(context,
        qtscript_QTreeView_function_names[_id],
        qtscript_QTreeView_function_signatures[_id]);
}

static QScriptValue qtscript_QTreeView_toScriptValue(QScriptEngine *engine, QTreeView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTreeView_fromScriptValue(const QScriptValue &value, QTreeView* &out)
{
    out = qobject_cast<QTreeView*>(value.toQObject());
}

QScriptValue qtscript_create_QTreeView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTreeView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTreeView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemView*>()));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTreeView_prototype_call, qtscript_QTreeView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTreeView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTreeView*>(engine, qtscript_QTreeView_toScriptValue, 
        qtscript_QTreeView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTreeView_static_call, proto, qtscript_QTreeView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
