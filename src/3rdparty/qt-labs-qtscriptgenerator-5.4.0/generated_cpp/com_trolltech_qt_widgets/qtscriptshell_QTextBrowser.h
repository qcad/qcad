#ifndef QTSCRIPTSHELL_QTEXTBROWSER_H
#define QTSCRIPTSHELL_QTEXTBROWSER_H

#include <qtextbrowser.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextBrowser : public QTextBrowser
{
public:
    QtScriptShell_QTextBrowser(QWidget*  parent = 0);
    ~QtScriptShell_QTextBrowser();

    void actionEvent(QActionEvent*  arg__1);
    void backward();
    bool  canInsertFromMimeData(const QMimeData*  source) const;
    void changeEvent(QEvent*  e);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  e);
    QMimeData*  createMimeDataFromSelection() const;
    void customEvent(QEvent*  arg__1);
    int  devType() const;
    void doSetTextCursor(const QTextCursor&  cursor);
    void dragEnterEvent(QDragEnterEvent*  e);
    void dragLeaveEvent(QDragLeaveEvent*  e);
    void dragMoveEvent(QDragMoveEvent*  e);
    void dropEvent(QDropEvent*  e);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  e);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  ev);
    void forward();
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    void home();
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  property) const;
    void insertFromMimeData(const QMimeData*  source);
    void keyPressEvent(QKeyEvent*  ev);
    void keyReleaseEvent(QKeyEvent*  e);
    void leaveEvent(QEvent*  arg__1);
    QVariant  loadResource(int  type, const QUrl&  name);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  e);
    void mouseMoveEvent(QMouseEvent*  ev);
    void mousePressEvent(QMouseEvent*  ev);
    void mouseReleaseEvent(QMouseEvent*  ev);
    void moveEvent(QMoveEvent*  arg__1);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  e);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void reload();
    void resizeEvent(QResizeEvent*  e);
    void scrollContentsBy(int  dx, int  dy);
    void setSource(const QUrl&  name);
    void setupViewport(QWidget*  viewport);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  arg__1);
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  e);
    bool  viewportEvent(QEvent*  arg__1);
    QSize  viewportSizeHint() const;
    void wheelEvent(QWheelEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTBROWSER_H
