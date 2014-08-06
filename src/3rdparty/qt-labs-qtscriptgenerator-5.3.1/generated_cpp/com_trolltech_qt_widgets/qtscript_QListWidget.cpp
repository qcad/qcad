#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlistwidget.h>
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
#include <qicon.h>
#include <qitemselectionmodel.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qmimedata.h>
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
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#include "qtscriptshell_QListWidget.h"

static const char * const qtscript_QListWidget_function_names[] = {
    "QListWidget"
    // static
    // prototype
    , "addItem"
    , "addItems"
    , "closePersistentEditor"
    , "currentItem"
    , "editItem"
    , "findItems"
    , "insertItem"
    , "insertItems"
    , "item"
    , "itemAt"
    , "itemWidget"
    , "openPersistentEditor"
    , "removeItemWidget"
    , "row"
    , "selectedItems"
    , "setCurrentItem"
    , "setItemWidget"
    , "sortItems"
    , "takeItem"
    , "visualItemRect"
    , "toString"
};

static const char * const qtscript_QListWidget_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QListWidgetItem item\nString label"
    , "List labels"
    , "QListWidgetItem item"
    , ""
    , "QListWidgetItem item"
    , "String text, MatchFlags flags"
    , "int row, QListWidgetItem item\nint row, String label"
    , "int row, List labels"
    , "int row"
    , "QPoint p\nint x, int y"
    , "QListWidgetItem item"
    , "QListWidgetItem item"
    , "QListWidgetItem item"
    , "QListWidgetItem item"
    , ""
    , "QListWidgetItem item\nQListWidgetItem item, SelectionFlags command"
    , "QListWidgetItem item, QWidget widget"
    , "SortOrder order"
    , "int row"
    , "QListWidgetItem item"
""
};

static const int qtscript_QListWidget_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 1
    , 2
    , 2
    , 2
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
    , 2
    , 2
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QListWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QListWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QListWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QListWidget*)
Q_DECLARE_METATYPE(QListWidgetItem*)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QList<QListWidgetItem* >)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(const QListWidgetItem*)
Q_DECLARE_METATYPE(QFlags<QItemSelectionModel::SelectionFlag>)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QListView*)

//
// QListWidget
//

static QScriptValue qtscript_QListWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QListWidget* _q_self = qscriptvalue_cast<QListWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QListWidget.%0(): this object is not a QListWidget")
            .arg(qtscript_QListWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QListWidgetItem*>(context->argument(0))) {
            QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
            _q_self->addItem(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->addItem(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->addItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        _q_self->closePersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QListWidgetItem* _q_result = _q_self->currentItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        _q_self->editItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<Qt::MatchFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(1));
        QList<QListWidgetItem* > _q_result = _q_self->findItems(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && qscriptvalue_cast<QListWidgetItem*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            QListWidgetItem* _q_arg1 = qscriptvalue_cast<QListWidgetItem*>(context->argument(1));
            _q_self->insertItem(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_arg1 = context->argument(1).toString();
            _q_self->insertItem(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QStringList _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->insertItems(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QListWidgetItem* _q_result = _q_self->item(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QListWidgetItem* _q_result = _q_self->itemAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QListWidgetItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        QWidget* _q_result = _q_self->itemWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        _q_self->openPersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        _q_self->removeItemWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        const QListWidgetItem* _q_arg0 = qscriptvalue_cast<const QListWidgetItem*>(context->argument(0));
        int _q_result = _q_self->row(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QList<QListWidgetItem* > _q_result = _q_self->selectedItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        _q_self->setCurrentItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        QFlags<QItemSelectionModel::SelectionFlag> _q_arg1 = qscriptvalue_cast<QFlags<QItemSelectionModel::SelectionFlag> >(context->argument(1));
        _q_self->setCurrentItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        QListWidgetItem* _q_arg0 = qscriptvalue_cast<QListWidgetItem*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        _q_self->setItemWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        _q_self->sortItems();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        Qt::SortOrder _q_arg0 = qscriptvalue_cast<Qt::SortOrder>(context->argument(0));
        _q_self->sortItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QListWidgetItem* _q_result = _q_self->takeItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        const QListWidgetItem* _q_arg0 = qscriptvalue_cast<const QListWidgetItem*>(context->argument(0));
        QRect _q_result = _q_self->visualItemRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20: {
    QString result = QString::fromLatin1("QListWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QListWidget_throw_ambiguity_error_helper(context,
        qtscript_QListWidget_function_names[_id+1],
        qtscript_QListWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QListWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QListWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QListWidget* _q_cpp_result = new QtScriptShell_QListWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QListWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QListWidget* _q_cpp_result = new QtScriptShell_QListWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QListWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QListWidget_throw_ambiguity_error_helper(context,
        qtscript_QListWidget_function_names[_id],
        qtscript_QListWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QListWidget_toScriptValue(QScriptEngine *engine, QListWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QListWidget_fromScriptValue(const QScriptValue &value, QListWidget* &out)
{
    out = qobject_cast<QListWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QListWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QListWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QListWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QListView*>()));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QListWidget_prototype_call, qtscript_QListWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QListWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QListWidget*>(engine, qtscript_QListWidget_toScriptValue, 
        qtscript_QListWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QListWidget_static_call, proto, qtscript_QListWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
