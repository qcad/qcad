#ifndef QTSCRIPTSHELL_QFORMLAYOUT_H
#define QTSCRIPTSHELL_QFORMLAYOUT_H

#include <qformlayout.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFormLayout : public QFormLayout
{
public:
    QtScriptShell_QFormLayout(QWidget*  parent = 0);
    ~QtScriptShell_QFormLayout();

    void addItem(QLayoutItem*  item);
    void childEvent(QChildEvent*  e);
    int  count() const;
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    Qt::Orientations  expandingDirections() const;
    QRect  geometry() const;
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  width) const;
    int  indexOf(QWidget*  arg__1) const;
    void invalidate();
    bool  isEmpty() const;
    QLayoutItem*  itemAt(int  index) const;
    QLayout*  layout();
    QSize  maximumSize() const;
    int  minimumHeightForWidth(int  arg__1) const;
    QSize  minimumSize() const;
    void setGeometry(const QRect&  rect);
    QSize  sizeHint() const;
    QSpacerItem*  spacerItem();
    QLayoutItem*  takeAt(int  index);
    void timerEvent(QTimerEvent*  arg__1);
    QWidget*  widget();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFORMLAYOUT_H
