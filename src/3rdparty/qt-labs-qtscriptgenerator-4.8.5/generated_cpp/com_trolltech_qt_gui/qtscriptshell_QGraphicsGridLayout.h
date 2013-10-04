#ifndef QTSCRIPTSHELL_QGRAPHICSGRIDLAYOUT_H
#define QTSCRIPTSHELL_QGRAPHICSGRIDLAYOUT_H

#include <qgraphicsgridlayout.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsGridLayout : public QGraphicsGridLayout
{
public:
    QtScriptShell_QGraphicsGridLayout(QGraphicsLayoutItem*  parent = 0);
    ~QtScriptShell_QGraphicsGridLayout();

    int  count() const;
    void getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const;
    void invalidate();
    QGraphicsLayoutItem*  itemAt(int  index) const;
    void removeAt(int  index);
    void setGeometry(const QRectF&  rect);
    QSizeF  sizeHint(Qt::SizeHint  which, const QSizeF&  constraint = QSizeF()) const;
    void updateGeometry();
    void widgetEvent(QEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSGRIDLAYOUT_H
