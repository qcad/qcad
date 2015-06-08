#ifndef QTSCRIPTSHELL_QGRAPHICSANCHORLAYOUT_H
#define QTSCRIPTSHELL_QGRAPHICSANCHORLAYOUT_H

#include <qgraphicsanchorlayout.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsAnchorLayout : public QGraphicsAnchorLayout
{
public:
    QtScriptShell_QGraphicsAnchorLayout(QGraphicsLayoutItem*  parent = 0);
    ~QtScriptShell_QGraphicsAnchorLayout();

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

#endif // QTSCRIPTSHELL_QGRAPHICSANCHORLAYOUT_H
