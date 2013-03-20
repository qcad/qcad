#ifndef QTSCRIPTSHELL_QGLWIDGET_H
#define QTSCRIPTSHELL_QGLWIDGET_H

#include <qgl.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGLWidget : public QGLWidget
{
public:
    QtScriptShell_QGLWidget(QGLContext*  context, QWidget*  parent = 0, const QGLWidget*  shareWidget = 0, Qt::WindowFlags  f = 0);
    QtScriptShell_QGLWidget(QWidget*  parent = 0, const QGLWidget*  shareWidget = 0, Qt::WindowFlags  f = 0);
    QtScriptShell_QGLWidget(const QGLFormat&  format, QWidget*  parent = 0, const QGLWidget*  shareWidget = 0, Qt::WindowFlags  f = 0);
    ~QtScriptShell_QGLWidget();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  arg__1);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  arg__1);
    void dragLeaveEvent(QDragLeaveEvent*  arg__1);
    void dragMoveEvent(QDragMoveEvent*  arg__1);
    void dropEvent(QDropEvent*  arg__1);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  arg__1);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  arg__1);
    void glDraw();
    void glInit();
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    void initializeGL();
    void initializeOverlayGL();
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  arg__1);
    void keyReleaseEvent(QKeyEvent*  arg__1);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    QSize  minimumSizeHint() const;
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  arg__1);
    void mousePressEvent(QMouseEvent*  arg__1);
    void mouseReleaseEvent(QMouseEvent*  arg__1);
    void moveEvent(QMoveEvent*  arg__1);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  arg__1);
    void paintGL();
    void paintOverlayGL();
    void resizeEvent(QResizeEvent*  arg__1);
    void resizeGL(int  w, int  h);
    void resizeOverlayGL(int  w, int  h);
    void showEvent(QShowEvent*  arg__1);
    QSize  sizeHint() const;
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  arg__1);
    void updateGL();
    void updateOverlayGL();
    void wheelEvent(QWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLWIDGET_H
