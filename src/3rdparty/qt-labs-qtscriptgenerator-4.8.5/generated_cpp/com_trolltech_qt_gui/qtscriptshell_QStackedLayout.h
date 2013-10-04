#ifndef QTSCRIPTSHELL_QSTACKEDLAYOUT_H
#define QTSCRIPTSHELL_QSTACKEDLAYOUT_H

#include <qstackedlayout.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStackedLayout : public QStackedLayout
{
public:
    QtScriptShell_QStackedLayout();
    QtScriptShell_QStackedLayout(QLayout*  parentLayout);
    QtScriptShell_QStackedLayout(QWidget*  parent);
    ~QtScriptShell_QStackedLayout();

    void addItem(QLayoutItem*  item);
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
    void setGeometry(const QRect&  rect);
    QSize  sizeHint() const;
    QSpacerItem*  spacerItem();
    QLayoutItem*  takeAt(int  arg__1);
    void timerEvent(QTimerEvent*  arg__1);
    QWidget*  widget();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTACKEDLAYOUT_H
