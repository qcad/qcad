#ifndef QTSCRIPTSHELL_QPLAINTEXTEDIT_H
#define QTSCRIPTSHELL_QPLAINTEXTEDIT_H

#include <qplaintextedit.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPlainTextEdit : public QPlainTextEdit
{
public:
    QtScriptShell_QPlainTextEdit(QWidget*  parent = 0);
    QtScriptShell_QPlainTextEdit(const QString&  text, QWidget*  parent = 0);
    ~QtScriptShell_QPlainTextEdit();

    void actionEvent(QActionEvent*  arg__1);
    bool  canInsertFromMimeData(const QMimeData*  source) const;
    void changeEvent(QEvent*  e);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  e);
    QMimeData*  createMimeDataFromSelection() const;
    void customEvent(QEvent*  arg__1);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  e);
    void dragLeaveEvent(QDragLeaveEvent*  e);
    void dragMoveEvent(QDragMoveEvent*  e);
    void dropEvent(QDropEvent*  e);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  e);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  e);
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  property) const;
    void insertFromMimeData(const QMimeData*  source);
    void keyPressEvent(QKeyEvent*  e);
    void keyReleaseEvent(QKeyEvent*  e);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    QVariant  loadResource(int  type, const QUrl&  name);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  e);
    void mouseMoveEvent(QMouseEvent*  e);
    void mousePressEvent(QMouseEvent*  e);
    void mouseReleaseEvent(QMouseEvent*  e);
    void moveEvent(QMoveEvent*  arg__1);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  e);
    void resizeEvent(QResizeEvent*  e);
    void scrollContentsBy(int  dx, int  dy);
    void showEvent(QShowEvent*  arg__1);
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  e);
    bool  viewportEvent(QEvent*  arg__1);
    void wheelEvent(QWheelEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPLAINTEXTEDIT_H
