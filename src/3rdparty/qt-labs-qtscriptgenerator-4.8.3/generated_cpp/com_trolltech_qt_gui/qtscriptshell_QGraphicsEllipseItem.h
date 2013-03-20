#ifndef QTSCRIPTSHELL_QGRAPHICSELLIPSEITEM_H
#define QTSCRIPTSHELL_QGRAPHICSELLIPSEITEM_H

#include <qgraphicsitem.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    QtScriptShell_QGraphicsEllipseItem(QGraphicsItem*  parent = 0, QGraphicsScene*  scene = 0);
    QtScriptShell_QGraphicsEllipseItem(const QRectF&  rect, QGraphicsItem*  parent = 0, QGraphicsScene*  scene = 0);
    QtScriptShell_QGraphicsEllipseItem(qreal  x, qreal  y, qreal  w, qreal  h, QGraphicsItem*  parent = 0, QGraphicsScene*  scene = 0);
    ~QtScriptShell_QGraphicsEllipseItem();

    void advance(int  phase);
    QRectF  boundingRect() const;
    bool  collidesWithItem(const QGraphicsItem*  other, Qt::ItemSelectionMode  mode) const;
    bool  collidesWithPath(const QPainterPath&  path, Qt::ItemSelectionMode  mode) const;
    bool  contains(const QPointF&  point) const;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*  event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent*  event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*  event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent*  event);
    void dropEvent(QGraphicsSceneDragDropEvent*  event);
    QVariant  extension(const QVariant&  variant) const;
    void focusInEvent(QFocusEvent*  event);
    void focusOutEvent(QFocusEvent*  event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*  event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*  event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent*  event);
    void inputMethodEvent(QInputMethodEvent*  event);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    bool  isObscuredBy(const QGraphicsItem*  item) const;
    QVariant  itemChange(QGraphicsItem::GraphicsItemChange  change, const QVariant&  value);
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*  event);
    void mousePressEvent(QGraphicsSceneMouseEvent*  event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*  event);
    QPainterPath  opaqueArea() const;
    void paint(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget = 0);
    bool  sceneEvent(QEvent*  event);
    bool  sceneEventFilter(QGraphicsItem*  watched, QEvent*  event);
    QPainterPath  shape() const;
    int  type() const;
    void wheelEvent(QGraphicsSceneWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSELLIPSEITEM_H
