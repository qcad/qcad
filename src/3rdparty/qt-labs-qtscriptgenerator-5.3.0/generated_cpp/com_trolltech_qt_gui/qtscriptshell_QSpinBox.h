#ifndef QTSCRIPTSHELL_QSPINBOX_H
#define QTSCRIPTSHELL_QSPINBOX_H

#include <qspinbox.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSpinBox : public QSpinBox
{
public:
    QtScriptShell_QSpinBox(QWidget*  parent = 0);
    ~QtScriptShell_QSpinBox();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  event);
    void childEvent(QChildEvent*  arg__1);
    void clear();
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  event);
    void customEvent(QEvent*  arg__1);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  arg__1);
    void dragLeaveEvent(QDragLeaveEvent*  arg__1);
    void dragMoveEvent(QDragMoveEvent*  arg__1);
    void dropEvent(QDropEvent*  arg__1);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fixup(QString&  str) const;
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  event);
    void mousePressEvent(QMouseEvent*  event);
    void mouseReleaseEvent(QMouseEvent*  event);
    void moveEvent(QMoveEvent*  arg__1);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  event);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  event);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  event);
    void stepBy(int  steps);
    QAbstractSpinBox::StepEnabled  stepEnabled() const;
    void tabletEvent(QTabletEvent*  arg__1);
    QString  textFromValue(int  val) const;
    void timerEvent(QTimerEvent*  event);
    QValidator::State  validate(QString&  input, int&  pos) const;
    int  valueFromText(const QString&  text) const;
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSPINBOX_H
