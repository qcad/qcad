#ifndef QTSCRIPTSHELL_QGRIDLAYOUT_H
#define QTSCRIPTSHELL_QGRIDLAYOUT_H

#include <qgridlayout.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGridLayout : public QGridLayout
{
public:
    QtScriptShell_QGridLayout();
    QtScriptShell_QGridLayout(QWidget*  parent);
    ~QtScriptShell_QGridLayout();

    void addItem(QLayoutItem*  arg__1);
    void childEvent(QChildEvent*  e);
    QSizePolicy::ControlTypes  controlTypes() const;
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
    QLayoutItem*  itemAt(int  index) const;
    QLayout*  layout();
    QSize  maximumSize() const;
    int  minimumHeightForWidth(int  arg__1) const;
    QSize  minimumSize() const;
    void setGeometry(const QRect&  arg__1);
    QSize  sizeHint() const;
    QSpacerItem*  spacerItem();
    QLayoutItem*  takeAt(int  index);
    void timerEvent(QTimerEvent*  arg__1);
    QWidget*  widget();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRIDLAYOUT_H
