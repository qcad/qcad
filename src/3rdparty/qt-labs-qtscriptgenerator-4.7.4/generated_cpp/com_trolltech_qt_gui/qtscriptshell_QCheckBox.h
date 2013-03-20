#ifndef QTSCRIPTSHELL_QCHECKBOX_H
#define QTSCRIPTSHELL_QCHECKBOX_H

#include <qcheckbox.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QCheckBox : public QCheckBox
{
public:
    QtScriptShell_QCheckBox(QWidget*  parent = 0);
    QtScriptShell_QCheckBox(const QString&  text, QWidget*  parent = 0);
    ~QtScriptShell_QCheckBox();

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
    void focusInEvent(QFocusEvent*  e);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  e);
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  arg__1);
    bool  hitButton(const QPoint&  pos) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  e);
    void keyReleaseEvent(QKeyEvent*  e);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    QSize  minimumSizeHint() const;
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  arg__1);
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

#endif // QTSCRIPTSHELL_QCHECKBOX_H
