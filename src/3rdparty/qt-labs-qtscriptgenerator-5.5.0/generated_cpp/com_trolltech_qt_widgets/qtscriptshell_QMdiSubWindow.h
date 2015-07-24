#ifndef QTSCRIPTSHELL_QMDISUBWINDOW_H
#define QTSCRIPTSHELL_QMDISUBWINDOW_H

#include <qmdisubwindow.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMdiSubWindow : public QMdiSubWindow
{
public:
    QtScriptShell_QMdiSubWindow(QWidget*  parent = 0, Qt::WindowFlags  flags = 0);
    ~QtScriptShell_QMdiSubWindow();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  changeEvent);
    void childEvent(QChildEvent*  childEvent);
    void closeEvent(QCloseEvent*  closeEvent);
    void contextMenuEvent(QContextMenuEvent*  contextMenuEvent);
    void customEvent(QEvent*  arg__1);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  arg__1);
    void dragLeaveEvent(QDragLeaveEvent*  arg__1);
    void dragMoveEvent(QDragMoveEvent*  arg__1);
    void dropEvent(QDropEvent*  arg__1);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  object, QEvent*  event);
    void focusInEvent(QFocusEvent*  focusInEvent);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  focusOutEvent);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  hideEvent);
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  keyEvent);
    void keyReleaseEvent(QKeyEvent*  arg__1);
    void leaveEvent(QEvent*  leaveEvent);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  mouseEvent);
    void mouseMoveEvent(QMouseEvent*  mouseEvent);
    void mousePressEvent(QMouseEvent*  mouseEvent);
    void mouseReleaseEvent(QMouseEvent*  mouseEvent);
    void moveEvent(QMoveEvent*  moveEvent);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  paintEvent);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  resizeEvent);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  showEvent);
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  timerEvent);
    void wheelEvent(QWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMDISUBWINDOW_H
