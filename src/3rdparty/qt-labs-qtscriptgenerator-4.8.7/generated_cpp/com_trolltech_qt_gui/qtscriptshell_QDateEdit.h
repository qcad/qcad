#ifndef QTSCRIPTSHELL_QDATEEDIT_H
#define QTSCRIPTSHELL_QDATEEDIT_H

#include <qdatetimeedit.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QDateEdit : public QDateEdit
{
public:
    QtScriptShell_QDateEdit(QWidget*  parent = 0);
    QtScriptShell_QDateEdit(const QDate&  date, QWidget*  parent = 0);
    ~QtScriptShell_QDateEdit();

    void actionEvent(QActionEvent*  arg__1);
    void changeEvent(QEvent*  event);
    void childEvent(QChildEvent*  arg__1);
    void clear();
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  event);
    void customEvent(QEvent*  arg__1);
    QDateTime  dateTimeFromText(const QString&  text) const;
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  arg__1);
    void dragLeaveEvent(QDragLeaveEvent*  arg__1);
    void dragMoveEvent(QDragMoveEvent*  arg__1);
    void dropEvent(QDropEvent*  arg__1);
    void enterEvent(QEvent*  arg__1);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fixup(QString&  input) const;
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void languageChange();
    void leaveEvent(QEvent*  arg__1);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  event);
    void mousePressEvent(QMouseEvent*  event);
    void mouseReleaseEvent(QMouseEvent*  event);
    void moveEvent(QMoveEvent*  arg__1);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  event);
    void resizeEvent(QResizeEvent*  event);
    void showEvent(QShowEvent*  event);
    void stepBy(int  steps);
    QAbstractSpinBox::StepEnabled  stepEnabled() const;
    void tabletEvent(QTabletEvent*  arg__1);
    QString  textFromDateTime(const QDateTime&  dt) const;
    void timerEvent(QTimerEvent*  event);
    QValidator::State  validate(QString&  input, int&  pos) const;
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDATEEDIT_H
