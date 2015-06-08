#ifndef QTSCRIPTSHELL_QGRAPHICSLINEARLAYOUT_H
#define QTSCRIPTSHELL_QGRAPHICSLINEARLAYOUT_H

#include <qgraphicslinearlayout.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsLinearLayout : public QGraphicsLinearLayout
{
public:
    QtScriptShell_QGraphicsLinearLayout(QGraphicsLayoutItem*  parent = 0);
    QtScriptShell_QGraphicsLinearLayout(Qt::Orientation  orientation, QGraphicsLayoutItem*  parent = 0);
    ~QtScriptShell_QGraphicsLinearLayout();

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

#endif // QTSCRIPTSHELL_QGRAPHICSLINEARLAYOUT_H
