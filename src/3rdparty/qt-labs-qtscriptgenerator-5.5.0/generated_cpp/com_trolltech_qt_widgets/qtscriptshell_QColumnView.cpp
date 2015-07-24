#include "qtscriptshell_QColumnView.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolumnview.h>
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
#include <qvector.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QActionEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractItemDelegate::EndEditHint)
Q_DECLARE_METATYPE(QCloseEvent*)
Q_DECLARE_METATYPE(QContextMenuEvent*)
Q_DECLARE_METATYPE(QAbstractItemView*)
Q_DECLARE_METATYPE(QVector<int >)
Q_DECLARE_METATYPE(QDragEnterEvent*)
Q_DECLARE_METATYPE(QDragLeaveEvent*)
Q_DECLARE_METATYPE(QDragMoveEvent*)
Q_DECLARE_METATYPE(QDropEvent*)
Q_DECLARE_METATYPE(QAbstractItemView::EditTrigger)
Q_DECLARE_METATYPE(QFocusEvent*)
Q_DECLARE_METATYPE(QHideEvent*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QInputMethodEvent*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QMouseEvent*)
Q_DECLARE_METATYPE(QMoveEvent*)
Q_DECLARE_METATYPE(long*)
Q_DECLARE_METATYPE(QPaintEngine*)
Q_DECLARE_METATYPE(QPaintEvent*)
Q_DECLARE_METATYPE(QPoint*)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QResizeEvent*)
Q_DECLARE_METATYPE(QAbstractItemView::ScrollHint)
//Q_DECLARE_METATYPE(QList<QModelIndex >)
//Q_DECLARE_METATYPE(QItemSelection)
Q_DECLARE_METATYPE(const QEvent*)
Q_DECLARE_METATYPE(QFlags<QItemSelectionModel::SelectionFlag>)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QItemSelectionModel*)
Q_DECLARE_METATYPE(QShowEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QTabletEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QWheelEvent*)

QtScriptShell_QColumnView::QtScriptShell_QColumnView(QWidget*  parent)
    : QColumnView(parent) {}

QtScriptShell_QColumnView::~QtScriptShell_QColumnView() {}

void QtScriptShell_QColumnView::actionEvent(QActionEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("actionEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actionEvent") & QScriptValue::QObjectMember)) {
        QColumnView::actionEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QColumnView::changeEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("changeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("changeEvent") & QScriptValue::QObjectMember)) {
        QColumnView::changeEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QColumnView::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QColumnView::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QColumnView::closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("closeEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEditor") & QScriptValue::QObjectMember)) {
        QColumnView::closeEditor(editor, hint);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, hint));
    }
}

void QtScriptShell_QColumnView::closeEvent(QCloseEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("closeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("closeEvent") & QScriptValue::QObjectMember)) {
        QColumnView::closeEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QColumnView::commitData(QWidget*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("commitData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("commitData") & QScriptValue::QObjectMember)) {
        QColumnView::commitData(editor);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
    }
}

void QtScriptShell_QColumnView::contextMenuEvent(QContextMenuEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("contextMenuEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("contextMenuEvent") & QScriptValue::QObjectMember)) {
        QColumnView::contextMenuEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QAbstractItemView*  QtScriptShell_QColumnView::createColumn(const QModelIndex&  rootIndex)
{
    QScriptValue _q_function = __qtscript_self.property("createColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createColumn") & QScriptValue::QObjectMember)) {
        return QColumnView::createColumn(rootIndex);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAbstractItemView* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rootIndex)));
    }
}

void QtScriptShell_QColumnView::currentChanged(const QModelIndex&  current, const QModelIndex&  previous)
{
    QScriptValue _q_function = __qtscript_self.property("currentChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentChanged") & QScriptValue::QObjectMember)) {
        QColumnView::currentChanged(current, previous);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, current)
            << qScriptValueFromValue(_q_engine, previous));
    }
}

void QtScriptShell_QColumnView::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QColumnView::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QColumnView::dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight, const QVector<int >&  roles)
{
    QScriptValue _q_function = __qtscript_self.property("dataChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dataChanged") & QScriptValue::QObjectMember)) {
        QColumnView::dataChanged(topLeft, bottomRight, roles);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, topLeft)
            << qScriptValueFromValue(_q_engine, bottomRight)
            << qScriptValueFromValue(_q_engine, roles));
    }
}

int  QtScriptShell_QColumnView::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)) {
        return QColumnView::devType();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QColumnView::doItemsLayout()
{
    QScriptValue _q_function = __qtscript_self.property("doItemsLayout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doItemsLayout") & QScriptValue::QObjectMember)) {
        QColumnView::doItemsLayout();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QColumnView::dragEnterEvent(QDragEnterEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragEnterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragEnterEvent") & QScriptValue::QObjectMember)) {
        QColumnView::dragEnterEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::dragLeaveEvent(QDragLeaveEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragLeaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragLeaveEvent") & QScriptValue::QObjectMember)) {
        QColumnView::dragLeaveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::dragMoveEvent(QDragMoveEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dragMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dragMoveEvent") & QScriptValue::QObjectMember)) {
        QColumnView::dragMoveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::dropEvent(QDropEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("dropEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("dropEvent") & QScriptValue::QObjectMember)) {
        QColumnView::dropEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

bool  QtScriptShell_QColumnView::edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("edit");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("edit") & QScriptValue::QObjectMember)) {
        return QColumnView::edit(index, trigger, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, trigger)
            << qScriptValueFromValue(_q_engine, event)));
    }
}

void QtScriptShell_QColumnView::editorDestroyed(QObject*  editor)
{
    QScriptValue _q_function = __qtscript_self.property("editorDestroyed");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("editorDestroyed") & QScriptValue::QObjectMember)) {
        QColumnView::editorDestroyed(editor);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor));
    }
}

void QtScriptShell_QColumnView::enterEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("enterEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("enterEvent") & QScriptValue::QObjectMember)) {
        QColumnView::enterEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QColumnView::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QColumnView::event(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QColumnView::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QColumnView::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

void QtScriptShell_QColumnView::focusInEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusInEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusInEvent") & QScriptValue::QObjectMember)) {
        QColumnView::focusInEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

bool  QtScriptShell_QColumnView::focusNextPrevChild(bool  next)
{
    QScriptValue _q_function = __qtscript_self.property("focusNextPrevChild");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusNextPrevChild") & QScriptValue::QObjectMember)) {
        return QColumnView::focusNextPrevChild(next);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, next)));
    }
}

void QtScriptShell_QColumnView::focusOutEvent(QFocusEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("focusOutEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("focusOutEvent") & QScriptValue::QObjectMember)) {
        QColumnView::focusOutEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

bool  QtScriptShell_QColumnView::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)) {
        return QColumnView::hasHeightForWidth();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QColumnView::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)) {
        return QColumnView::heightForWidth(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

void QtScriptShell_QColumnView::hideEvent(QHideEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("hideEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hideEvent") & QScriptValue::QObjectMember)) {
        QColumnView::hideEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QColumnView::horizontalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("horizontalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalOffset") & QScriptValue::QObjectMember)) {
        return QColumnView::horizontalOffset();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QColumnView::horizontalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarAction") & QScriptValue::QObjectMember)) {
        QColumnView::horizontalScrollbarAction(action);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
    }
}

void QtScriptShell_QColumnView::horizontalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("horizontalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("horizontalScrollbarValueChanged") & QScriptValue::QObjectMember)) {
        QColumnView::horizontalScrollbarValueChanged(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

QModelIndex  QtScriptShell_QColumnView::indexAt(const QPoint&  point) const
{
    QScriptValue _q_function = __qtscript_self.property("indexAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexAt") & QScriptValue::QObjectMember)) {
        return QColumnView::indexAt(point);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QModelIndex >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, point)));
    }
}

void QtScriptShell_QColumnView::initPainter(QPainter*  painter) const
{
    QScriptValue _q_function = __qtscript_self.property("initPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("initPainter") & QScriptValue::QObjectMember)) {
        QColumnView::initPainter(painter);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter));
    }
}

void QtScriptShell_QColumnView::inputMethodEvent(QInputMethodEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodEvent") & QScriptValue::QObjectMember)) {
        QColumnView::inputMethodEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

QVariant  QtScriptShell_QColumnView::inputMethodQuery(Qt::InputMethodQuery  query) const
{
    QScriptValue _q_function = __qtscript_self.property("inputMethodQuery");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("inputMethodQuery") & QScriptValue::QObjectMember)) {
        return QColumnView::inputMethodQuery(query);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, query)));
    }
}

bool  QtScriptShell_QColumnView::isIndexHidden(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("isIndexHidden");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isIndexHidden") & QScriptValue::QObjectMember)) {
        return QColumnView::isIndexHidden(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

void QtScriptShell_QColumnView::keyPressEvent(QKeyEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("keyPressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyPressEvent") & QScriptValue::QObjectMember)) {
        QColumnView::keyPressEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::keyReleaseEvent(QKeyEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("keyReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyReleaseEvent") & QScriptValue::QObjectMember)) {
        QColumnView::keyReleaseEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QColumnView::keyboardSearch(const QString&  search)
{
    QScriptValue _q_function = __qtscript_self.property("keyboardSearch");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("keyboardSearch") & QScriptValue::QObjectMember)) {
        QColumnView::keyboardSearch(search);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, search));
    }
}

void QtScriptShell_QColumnView::leaveEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("leaveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("leaveEvent") & QScriptValue::QObjectMember)) {
        QColumnView::leaveEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QColumnView::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        return QColumnView::metric(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

void QtScriptShell_QColumnView::mouseDoubleClickEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseDoubleClickEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseDoubleClickEvent") & QScriptValue::QObjectMember)) {
        QColumnView::mouseDoubleClickEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::mouseMoveEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseMoveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseMoveEvent") & QScriptValue::QObjectMember)) {
        QColumnView::mouseMoveEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::mousePressEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mousePressEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mousePressEvent") & QScriptValue::QObjectMember)) {
        QColumnView::mousePressEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::mouseReleaseEvent(QMouseEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("mouseReleaseEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("mouseReleaseEvent") & QScriptValue::QObjectMember)) {
        QColumnView::mouseReleaseEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::moveEvent(QMoveEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("moveEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("moveEvent") & QScriptValue::QObjectMember)) {
        QColumnView::moveEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QColumnView::nativeEvent(const QByteArray&  eventType, void*  message, long*  result)
{
    QScriptValue _q_function = __qtscript_self.property("nativeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nativeEvent") & QScriptValue::QObjectMember)) {
        return QColumnView::nativeEvent(eventType, message, result);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, eventType)
            << qScriptValueFromValue(_q_engine, message)
            << qScriptValueFromValue(_q_engine, result)));
    }
}

QPaintEngine*  QtScriptShell_QColumnView::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)) {
        return QColumnView::paintEngine();
    } else {
        return qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QColumnView::paintEvent(QPaintEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("paintEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEvent") & QScriptValue::QObjectMember)) {
        QColumnView::paintEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QPaintDevice*  QtScriptShell_QColumnView::redirected(QPoint*  offset) const
{
    QScriptValue _q_function = __qtscript_self.property("redirected");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("redirected") & QScriptValue::QObjectMember)) {
        return QColumnView::redirected(offset);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPaintDevice* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, offset)));
    }
}

void QtScriptShell_QColumnView::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)) {
        QColumnView::reset();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QColumnView::resizeEvent(QResizeEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("resizeEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("resizeEvent") & QScriptValue::QObjectMember)) {
        QColumnView::resizeEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsAboutToBeRemoved");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsAboutToBeRemoved") & QScriptValue::QObjectMember)) {
        QColumnView::rowsAboutToBeRemoved(parent, start, end);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, start)
            << qScriptValueFromValue(_q_engine, end));
    }
}

void QtScriptShell_QColumnView::rowsInserted(const QModelIndex&  parent, int  start, int  end)
{
    QScriptValue _q_function = __qtscript_self.property("rowsInserted");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("rowsInserted") & QScriptValue::QObjectMember)) {
        QColumnView::rowsInserted(parent, start, end);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, start)
            << qScriptValueFromValue(_q_engine, end));
    }
}

void QtScriptShell_QColumnView::scrollContentsBy(int  dx, int  dy)
{
    QScriptValue _q_function = __qtscript_self.property("scrollContentsBy");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollContentsBy") & QScriptValue::QObjectMember)) {
        QColumnView::scrollContentsBy(dx, dy);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, dx)
            << qScriptValueFromValue(_q_engine, dy));
    }
}

void QtScriptShell_QColumnView::scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint)
{
    QScriptValue _q_function = __qtscript_self.property("scrollTo");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("scrollTo") & QScriptValue::QObjectMember)) {
        QColumnView::scrollTo(index, hint);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, hint));
    }
}

void QtScriptShell_QColumnView::selectAll()
{
    QScriptValue _q_function = __qtscript_self.property("selectAll");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectAll") & QScriptValue::QObjectMember)) {
        QColumnView::selectAll();
    } else {
        _q_function.call(__qtscript_self);
    }
}

QList<QModelIndex >  QtScriptShell_QColumnView::selectedIndexes() const
{
    QScriptValue _q_function = __qtscript_self.property("selectedIndexes");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectedIndexes") & QScriptValue::QObjectMember)) {
        return QColumnView::selectedIndexes();
    } else {
        return qscriptvalue_cast<QList<QModelIndex > >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QColumnView::selectionChanged(const QItemSelection&  selected, const QItemSelection&  deselected)
{
    QScriptValue _q_function = __qtscript_self.property("selectionChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionChanged") & QScriptValue::QObjectMember)) {
        QColumnView::selectionChanged(selected, deselected);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selected)
            << qScriptValueFromValue(_q_engine, deselected));
    }
}

QItemSelectionModel::SelectionFlags  QtScriptShell_QColumnView::selectionCommand(const QModelIndex&  index, const QEvent*  event) const
{
    QScriptValue _q_function = __qtscript_self.property("selectionCommand");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("selectionCommand") & QScriptValue::QObjectMember)) {
        return QColumnView::selectionCommand(index, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QItemSelectionModel::SelectionFlags >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)
            << qScriptValueFromValue(_q_engine, const_cast<const QEvent *>(event))));
    }
}

void QtScriptShell_QColumnView::setModel(QAbstractItemModel*  model)
{
    QScriptValue _q_function = __qtscript_self.property("setModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setModel") & QScriptValue::QObjectMember)) {
        QColumnView::setModel(model);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, model));
    }
}

void QtScriptShell_QColumnView::setRootIndex(const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("setRootIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setRootIndex") & QScriptValue::QObjectMember)) {
        QColumnView::setRootIndex(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index));
    }
}

void QtScriptShell_QColumnView::setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  command)
{
    QScriptValue _q_function = __qtscript_self.property("setSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelection") & QScriptValue::QObjectMember)) {
        QColumnView::setSelection(rect, command);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, command));
    }
}

void QtScriptShell_QColumnView::setSelectionModel(QItemSelectionModel*  selectionModel)
{
    QScriptValue _q_function = __qtscript_self.property("setSelectionModel");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setSelectionModel") & QScriptValue::QObjectMember)) {
        QColumnView::setSelectionModel(selectionModel);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selectionModel));
    }
}

void QtScriptShell_QColumnView::setupViewport(QWidget*  viewport)
{
    QScriptValue _q_function = __qtscript_self.property("setupViewport");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setupViewport") & QScriptValue::QObjectMember)) {
        QColumnView::setupViewport(viewport);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, viewport));
    }
}

QPainter*  QtScriptShell_QColumnView::sharedPainter() const
{
    QScriptValue _q_function = __qtscript_self.property("sharedPainter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sharedPainter") & QScriptValue::QObjectMember)) {
        return QColumnView::sharedPainter();
    } else {
        return qscriptvalue_cast<QPainter* >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QColumnView::showEvent(QShowEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("showEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("showEvent") & QScriptValue::QObjectMember)) {
        QColumnView::showEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

int  QtScriptShell_QColumnView::sizeHintForColumn(int  column) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForColumn");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForColumn") & QScriptValue::QObjectMember)) {
        return QColumnView::sizeHintForColumn(column);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, column)));
    }
}

int  QtScriptShell_QColumnView::sizeHintForRow(int  row) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHintForRow");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHintForRow") & QScriptValue::QObjectMember)) {
        return QColumnView::sizeHintForRow(row);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, row)));
    }
}

void QtScriptShell_QColumnView::startDrag(Qt::DropActions  supportedActions)
{
    QScriptValue _q_function = __qtscript_self.property("startDrag");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("startDrag") & QScriptValue::QObjectMember)) {
        QColumnView::startDrag(supportedActions);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, supportedActions));
    }
}

void QtScriptShell_QColumnView::tabletEvent(QTabletEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("tabletEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("tabletEvent") & QScriptValue::QObjectMember)) {
        QColumnView::tabletEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QColumnView::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QColumnView::timerEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QColumnView::updateEditorData()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorData") & QScriptValue::QObjectMember)) {
        QColumnView::updateEditorData();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QColumnView::updateEditorGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorGeometries") & QScriptValue::QObjectMember)) {
        QColumnView::updateEditorGeometries();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QColumnView::updateGeometries()
{
    QScriptValue _q_function = __qtscript_self.property("updateGeometries");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateGeometries") & QScriptValue::QObjectMember)) {
        QColumnView::updateGeometries();
    } else {
        _q_function.call(__qtscript_self);
    }
}

int  QtScriptShell_QColumnView::verticalOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("verticalOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalOffset") & QScriptValue::QObjectMember)) {
        return QColumnView::verticalOffset();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QColumnView::verticalScrollbarAction(int  action)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarAction") & QScriptValue::QObjectMember)) {
        QColumnView::verticalScrollbarAction(action);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, action));
    }
}

void QtScriptShell_QColumnView::verticalScrollbarValueChanged(int  value)
{
    QScriptValue _q_function = __qtscript_self.property("verticalScrollbarValueChanged");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("verticalScrollbarValueChanged") & QScriptValue::QObjectMember)) {
        QColumnView::verticalScrollbarValueChanged(value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value));
    }
}

QStyleOptionViewItem  QtScriptShell_QColumnView::viewOptions() const
{
    QScriptValue _q_function = __qtscript_self.property("viewOptions");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewOptions") & QScriptValue::QObjectMember)) {
        return QColumnView::viewOptions();
    } else {
        return qscriptvalue_cast<QStyleOptionViewItem >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QColumnView::viewportEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("viewportEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportEvent") & QScriptValue::QObjectMember)) {
        return QColumnView::viewportEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

QSize  QtScriptShell_QColumnView::viewportSizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("viewportSizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("viewportSizeHint") & QScriptValue::QObjectMember)) {
        return QColumnView::viewportSizeHint();
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QColumnView::visualRect(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRect") & QScriptValue::QObjectMember)) {
        return QColumnView::visualRect(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

QRegion  QtScriptShell_QColumnView::visualRegionForSelection(const QItemSelection&  selection) const
{
    QScriptValue _q_function = __qtscript_self.property("visualRegionForSelection");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("visualRegionForSelection") & QScriptValue::QObjectMember)) {
        return QColumnView::visualRegionForSelection(selection);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRegion >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, selection)));
    }
}

void QtScriptShell_QColumnView::wheelEvent(QWheelEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("wheelEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("wheelEvent") & QScriptValue::QObjectMember)) {
        QColumnView::wheelEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

