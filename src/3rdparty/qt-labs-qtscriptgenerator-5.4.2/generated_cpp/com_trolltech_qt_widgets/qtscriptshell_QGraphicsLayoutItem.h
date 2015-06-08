#ifndef QTSCRIPTSHELL_QGRAPHICSLAYOUTITEM_H
#define QTSCRIPTSHELL_QGRAPHICSLAYOUTITEM_H

#include <qgraphicslayoutitem.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsLayoutItem : public QGraphicsLayoutItem
{
public:
    QtScriptShell_QGraphicsLayoutItem(QGraphicsLayoutItem*  parent = 0, bool  isLayout = false);
    ~QtScriptShell_QGraphicsLayoutItem();

    void getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const;
    void setGeometry(const QRectF&  rect);
    QSizeF  sizeHint(Qt::SizeHint  which, const QSizeF&  constraint = QSizeF()) const;
    void updateGeometry();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSLAYOUTITEM_H
