#ifndef QTSCRIPTSHELL_QGRAPHICSVIEW_H
#define QTSCRIPTSHELL_QGRAPHICSVIEW_H

#include <qgraphicsview.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsView : public QGraphicsView
{
public:
    QtScriptShell_QGraphicsView(QGraphicsScene*  scene, QWidget*  parent = 0);
    QtScriptShell_QGraphicsView(QWidget*  parent = 0);
    ~QtScriptShell_QGraphicsView();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  arg__1);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  event);
    void customEvent(QEvent*  arg__1);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  event);
    void dragMoveEvent(QDragMoveEvent*  event);
    void drawBackground(QPainter*  painter, const QRectF&  rect);
    void drawForeground(QPainter*  painter, const QRectF&  rect);
    void drawItems(QPainter*  painter, int  numItems, QGraphicsItem**  items, const QStyleOptionGraphicsItem*  options);
    void dropEvent(QDropEvent*  event);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    void inputMethodEvent(QInputMethodEvent*  event);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  event);
    void mousePressEvent(QMouseEvent*  event);
    void mouseReleaseEvent(QMouseEvent*  event);
    void moveEvent(QMoveEvent*  arg__1);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  event);
    void resizeEvent(QResizeEvent*  event);
    void scrollContentsBy(int  dx, int  dy);
    void showEvent(QShowEvent*  event);
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  arg__1);
    bool  viewportEvent(QEvent*  event);
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSVIEW_H
