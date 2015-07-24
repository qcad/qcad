#ifndef QTSCRIPTSHELL_QWIDGETITEM_H
#define QTSCRIPTSHELL_QWIDGETITEM_H

#include <qlayoutitem.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWidgetItem : public QWidgetItem
{
public:
    QtScriptShell_QWidgetItem(QWidget*  w);
    ~QtScriptShell_QWidgetItem();

    QSizePolicy::ControlTypes  controlTypes() const;
    Qt::Orientations  expandingDirections() const;
    QRect  geometry() const;
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void invalidate();
    bool  isEmpty() const;
    QLayout*  layout();
    QSize  maximumSize() const;
    int  minimumHeightForWidth(int  arg__1) const;
    QSize  minimumSize() const;
    void setGeometry(const QRect&  arg__1);
    QSize  sizeHint() const;
    QSpacerItem*  spacerItem();
    QWidget*  widget();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWIDGETITEM_H
