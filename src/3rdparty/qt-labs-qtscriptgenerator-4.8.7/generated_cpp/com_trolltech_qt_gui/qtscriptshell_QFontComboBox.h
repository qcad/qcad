#ifndef QTSCRIPTSHELL_QFONTCOMBOBOX_H
#define QTSCRIPTSHELL_QFONTCOMBOBOX_H

#include <qfontcombobox.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFontComboBox : public QFontComboBox
{
public:
    QtScriptShell_QFontComboBox(QWidget*  parent = 0);
    ~QtScriptShell_QFontComboBox();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  e);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  e);
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
    void hideEvent(QHideEvent*  e);
    void hidePopup();
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  e);
    void keyReleaseEvent(QKeyEvent*  e);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  arg__1);
    void mousePressEvent(QMouseEvent*  e);
    void mouseReleaseEvent(QMouseEvent*  e);
    void moveEvent(QMoveEvent*  arg__1);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  e);
    void resizeEvent(QResizeEvent*  e);
    void showEvent(QShowEvent*  e);
    void showPopup();
    void tabletEvent(QTabletEvent*  arg__1);
    void timerEvent(QTimerEvent*  arg__1);
    void wheelEvent(QWheelEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFONTCOMBOBOX_H
