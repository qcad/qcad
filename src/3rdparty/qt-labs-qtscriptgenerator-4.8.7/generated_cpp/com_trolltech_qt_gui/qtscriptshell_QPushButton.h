#ifndef QTSCRIPTSHELL_QPUSHBUTTON_H
#define QTSCRIPTSHELL_QPUSHBUTTON_H

#include <qpushbutton.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPushButton : public QPushButton
{
public:
    QtScriptShell_QPushButton(QWidget*  parent = 0);
    QtScriptShell_QPushButton(const QIcon&  icon, const QString&  text, QWidget*  parent = 0);
    QtScriptShell_QPushButton(const QString&  text, QWidget*  parent = 0);
    ~QtScriptShell_QPushButton();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  e);
    void checkStateSet();
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
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  arg__1);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  arg__1);
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    bool  hitButton(const QPoint&  pos) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  arg__1);
    void keyReleaseEvent(QKeyEvent*  e);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  e);
    void mousePressEvent(QMouseEvent*  e);
    void mouseReleaseEvent(QMouseEvent*  e);
    void moveEvent(QMoveEvent*  arg__1);
    void nextCheckState();
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  arg__1);
    void resizeEvent(QResizeEvent*  arg__1);
    void showEvent(QShowEvent*  arg__1);
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  e);
    void wheelEvent(QWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPUSHBUTTON_H
