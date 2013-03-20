#ifndef QTSCRIPTSHELL_QMESSAGEBOX_H
#define QTSCRIPTSHELL_QMESSAGEBOX_H

#include <qmessagebox.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QMessageBox : public QMessageBox
{
public:
    QtScriptShell_QMessageBox(QMessageBox::Icon  icon, const QString&  title, const QString&  text, QMessageBox::StandardButtons  buttons = NoButton, QWidget*  parent = 0, Qt::WindowFlags  flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    QtScriptShell_QMessageBox(QWidget*  parent = 0);
    QtScriptShell_QMessageBox(const QString&  title, const QString&  text, QMessageBox::Icon  icon, int  button0, int  button1, int  button2, QWidget*  parent = 0, Qt::WindowFlags  f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ~QtScriptShell_QMessageBox();

    void accept();
    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  event);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    int  devType() const;
    void done(int  arg__1);
    void dragEnterEvent(QDragEnterEvent*  arg__1);
    void dragLeaveEvent(QDragLeaveEvent*  arg__1);
    void dragMoveEvent(QDragMoveEvent*  arg__1);
    void dropEvent(QDropEvent*  arg__1);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  arg__1);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  arg__1);
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  arg__1);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  arg__1);
    void mousePressEvent(QMouseEvent*  arg__1);
    void mouseReleaseEvent(QMouseEvent*  arg__1);
    void moveEvent(QMoveEvent*  arg__1);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  arg__1);
    void reject();
    void resizeEvent(QResizeEvent*  event);
    void showEvent(QShowEvent*  event);
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  arg__1);
    void wheelEvent(QWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMESSAGEBOX_H
