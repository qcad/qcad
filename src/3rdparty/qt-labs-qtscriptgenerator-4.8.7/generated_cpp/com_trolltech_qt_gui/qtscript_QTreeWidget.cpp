#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtreewidget.h>
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
#include <qtreewidget.h>
#include <qwidget.h>

#include "qtscriptshell_QTreeWidget.h"

static const char * const qtscript_QTreeWidget_function_names[] = {
    "QTreeWidget"
    // static
    // prototype
    , "addTopLevelItem"
    , "addTopLevelItems"
    , "closePersistentEditor"
    , "currentColumn"
    , "currentItem"
    , "editItem"
    , "findItems"
    , "headerItem"
    , "indexOfTopLevelItem"
    , "insertTopLevelItem"
    , "insertTopLevelItems"
    , "invisibleRootItem"
    , "isFirstItemColumnSpanned"
    , "itemAbove"
    , "itemAt"
    , "itemBelow"
    , "itemWidget"
    , "openPersistentEditor"
    , "removeItemWidget"
    , "selectedItems"
    , "setCurrentItem"
    , "setFirstItemColumnSpanned"
    , "setHeaderItem"
    , "setHeaderLabel"
    , "setHeaderLabels"
    , "setItemWidget"
    , "sortColumn"
    , "sortItems"
    , "takeTopLevelItem"
    , "topLevelItem"
    , "visualItemRect"
    , "toString"
};

static const char * const qtscript_QTreeWidget_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QTreeWidgetItem item"
    , "List items"
    , "QTreeWidgetItem item, int column"
    , ""
    , ""
    , "QTreeWidgetItem item, int column"
    , "String text, MatchFlags flags, int column"
    , ""
    , "QTreeWidgetItem item"
    , "int index, QTreeWidgetItem item"
    , "int index, List items"
    , ""
    , "QTreeWidgetItem item"
    , "QTreeWidgetItem item"
    , "QPoint p\nint x, int y"
    , "QTreeWidgetItem item"
    , "QTreeWidgetItem item, int column"
    , "QTreeWidgetItem item, int column"
    , "QTreeWidgetItem item, int column"
    , ""
    , "QTreeWidgetItem item\nQTreeWidgetItem item, int column\nQTreeWidgetItem item, int column, SelectionFlags command"
    , "QTreeWidgetItem item, bool span"
    , "QTreeWidgetItem item"
    , "String label"
    , "List labels"
    , "QTreeWidgetItem item, int column, QWidget widget"
    , ""
    , "int column, SortOrder order"
    , "int index"
    , "int index"
    , "QTreeWidgetItem item"
""
};

static const int qtscript_QTreeWidget_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 2
    , 0
    , 0
    , 2
    , 3
    , 0
    , 1
    , 2
    , 2
    , 0
    , 1
    , 1
    , 2
    , 1
    , 2
    , 2
    , 2
    , 0
    , 3
    , 2
    , 1
    , 1
    , 1
    , 3
    , 0
    , 2
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QTreeWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTreeWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTreeWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QTreeWidget*)
Q_DECLARE_METATYPE(QTreeWidgetItem*)
Q_DECLARE_METATYPE(QList<QTreeWidgetItem*>)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QFlags<QItemSelectionModel::SelectionFlag>)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QTreeView*)

//
// QTreeWidget
//

static QScriptValue qtscript_QTreeWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 31;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTreeWidget* _q_self = qscriptvalue_cast<QTreeWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTreeWidget.%0(): this object is not a QTreeWidget")
            .arg(qtscript_QTreeWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->addTopLevelItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QList<QTreeWidgetItem*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->addTopLevelItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->closePersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->closePersistentEditor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
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
        QTreeWidgetItem* _q_result = _q_self->currentItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->editItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->editItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<Qt::MatchFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(1));
        QList<QTreeWidgetItem*> _q_result = _q_self->findItems(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<Qt::MatchFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QList<QTreeWidgetItem*> _q_result = _q_self->findItems(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QTreeWidgetItem* _q_result = _q_self->headerItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_result = _q_self->indexOfTopLevelItem(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTreeWidgetItem* _q_arg1 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1));
        _q_self->insertTopLevelItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QTreeWidgetItem*> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->insertTopLevelItems(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QTreeWidgetItem* _q_result = _q_self->invisibleRootItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        bool _q_result = _q_self->isFirstItemColumnSpanned(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        QTreeWidgetItem* _q_result = _q_self->itemAbove(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QTreeWidgetItem* _q_result = _q_self->itemAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTreeWidgetItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        QTreeWidgetItem* _q_result = _q_self->itemBelow(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_result = _q_self->itemWidget(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->openPersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->openPersistentEditor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->removeItemWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QList<QTreeWidgetItem*> _q_result = _q_self->selectedItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->setCurrentItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setCurrentItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<QItemSelectionModel::SelectionFlag> _q_arg2 = qscriptvalue_cast<QFlags<QItemSelectionModel::SelectionFlag> >(context->argument(2));
        _q_self->setCurrentItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setFirstItemColumnSpanned(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->setHeaderItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHeaderLabel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setHeaderLabels(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 3) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        _q_self->setItemWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->sortColumn();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
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
        QTreeWidgetItem* _q_result = _q_self->takeTopLevelItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTreeWidgetItem* _q_result = _q_self->topLevelItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        QRect _q_result = _q_self->visualItemRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31: {
    QString result = QString::fromLatin1("QTreeWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTreeWidget_throw_ambiguity_error_helper(context,
        qtscript_QTreeWidget_function_names[_id+1],
        qtscript_QTreeWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTreeWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTreeWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTreeWidget* _q_cpp_result = new QtScriptShell_QTreeWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTreeWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QTreeWidget* _q_cpp_result = new QtScriptShell_QTreeWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTreeWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTreeWidget_throw_ambiguity_error_helper(context,
        qtscript_QTreeWidget_function_names[_id],
        qtscript_QTreeWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QTreeWidget_toScriptValue(QScriptEngine *engine, QTreeWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTreeWidget_fromScriptValue(const QScriptValue &value, QTreeWidget* &out)
{
    out = qobject_cast<QTreeWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QTreeWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTreeWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTreeWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTreeView*>()));
    for (int i = 0; i < 32; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTreeWidget_prototype_call, qtscript_QTreeWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTreeWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTreeWidget*>(engine, qtscript_QTreeWidget_toScriptValue, 
        qtscript_QTreeWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTreeWidget_static_call, proto, qtscript_QTreeWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
