#ifndef QTSCRIPTSHELL_QCOLUMNVIEW_H
#define QTSCRIPTSHELL_QCOLUMNVIEW_H

#include <qcolumnview.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QColumnView : public QColumnView
{
public:
    QtScriptShell_QColumnView(QWidget*  parent = 0);
    ~QtScriptShell_QColumnView();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  arg__1);
    void childEvent(QChildEvent*  arg__1);
    void closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint);
    void closeEvent(QCloseEvent*  arg__1);
    void commitData(QWidget*  editor);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    QAbstractItemView*  createColumn(const QModelIndex&  rootIndex);
    void currentChanged(const QModelIndex&  current, const QModelIndex&  previous);
    void customEvent(QEvent*  arg__1);
    void dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight);
    int  devType() const;
    void doItemsLayout();
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  event);
    void dragMoveEvent(QDragMoveEvent*  event);
    void dropEvent(QDropEvent*  event);
    bool  edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event);
    void editorDestroyed(QObject*  editor);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    int  horizontalOffset() const;
    void horizontalScrollbarAction(int  action);
    void horizontalScrollbarValueChanged(int  value);
    QModelIndex  indexAt(const QPoint&  point) const;
    void inputMethodEvent(QInputMethodEvent*  event);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    bool  isIndexHidden(const QModelIndex&  index) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  arg__1);
    void keyboardSearch(const QString&  search);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  event);
    void mousePressEvent(QMouseEvent*  event);
    void mouseReleaseEvent(QMouseEvent*  event);
    void moveEvent(QMoveEvent*  arg__1);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  arg__1);
    void reset();
    void resizeEvent(QResizeEvent*  event);
    void rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end);
    void rowsInserted(const QModelIndex&  parent, int  start, int  end);
    void scrollContentsBy(int  dx, int  dy);
    void scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint = QAbstractItemView::EnsureVisible);
    void selectAll();
    QList<QModelIndex >  selectedIndexes() const;
    void selectionChanged(const QItemSelection&  selected, const QItemSelection&  deselected);
    QItemSelectionModel::SelectionFlags  selectionCommand(const QModelIndex&  index, const QEvent*  event) const;
    void setModel(QAbstractItemModel*  model);
    void setRootIndex(const QModelIndex&  index);
    void setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  command);
    void setSelectionModel(QItemSelectionModel*  selectionModel);
    void showEvent(QShowEvent*  arg__1);
    int  sizeHintForColumn(int  column) const;
    int  sizeHintForRow(int  row) const;
    void startDrag(Qt::DropActions  supportedActions);
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  event);
    void updateEditorData();
    void updateEditorGeometries();
    void updateGeometries();
    int  verticalOffset() const;
    void verticalScrollbarAction(int  action);
    void verticalScrollbarValueChanged(int  value);
    QStyleOptionViewItem  viewOptions() const;
    bool  viewportEvent(QEvent*  event);
    QRect  visualRect(const QModelIndex&  index) const;
    QRegion  visualRegionForSelection(const QItemSelection&  selection) const;
    void wheelEvent(QWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCOLUMNVIEW_H
