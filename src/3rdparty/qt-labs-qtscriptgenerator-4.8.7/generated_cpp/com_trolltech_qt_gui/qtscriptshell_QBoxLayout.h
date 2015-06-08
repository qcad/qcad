#ifndef QTSCRIPTSHELL_QBOXLAYOUT_H
#define QTSCRIPTSHELL_QBOXLAYOUT_H

#include <qboxlayout.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QBoxLayout : public QBoxLayout
{
public:
    QtScriptShell_QBoxLayout(QBoxLayout::Direction  arg__1, QWidget*  parent = 0);
    ~QtScriptShell_QBoxLayout();

    void addItem(QLayoutItem*  arg__1);
    void childEvent(QChildEvent*  e);
    int  count() const;
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    Qt::Orientations  expandingDirections() const;
    QRect  geometry() const;
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    int  indexOf(QWidget*  arg__1) const;
    void invalidate();
    bool  isEmpty() const;
    QLayoutItem*  itemAt(int  arg__1) const;
    QLayout*  layout();
    QSize  maximumSize() const;
    int  minimumHeightForWidth(int  arg__1) const;
    QSize  minimumSize() const;
    void setGeometry(const QRect&  arg__1);
    QSize  sizeHint() const;
    QSpacerItem*  spacerItem();
    QLayoutItem*  takeAt(int  arg__1);
    void timerEvent(QTimerEvent*  arg__1);
    QWidget*  widget();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBOXLAYOUT_H
