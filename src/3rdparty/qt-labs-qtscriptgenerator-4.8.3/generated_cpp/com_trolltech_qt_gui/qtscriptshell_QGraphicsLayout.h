#ifndef QTSCRIPTSHELL_QGRAPHICSLAYOUT_H
#define QTSCRIPTSHELL_QGRAPHICSLAYOUT_H

#include <qgraphicslayout.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsLayout : public QGraphicsLayout
{
public:
    QtScriptShell_QGraphicsLayout(QGraphicsLayoutItem*  parent = 0);
    ~QtScriptShell_QGraphicsLayout();

    int  count() const;
    void getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const;
    void invalidate();
    QGraphicsLayoutItem*  itemAt(int  i) const;
    void removeAt(int  index);
    void setGeometry(const QRectF&  rect);
    QSizeF  sizeHint(Qt::SizeHint  which, const QSizeF&  constraint) const;
    void updateGeometry();
    void widgetEvent(QEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSLAYOUT_H
