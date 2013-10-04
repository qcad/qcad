#ifndef QTSCRIPTSHELL_QGRAPHICSSCENE_H
#define QTSCRIPTSHELL_QGRAPHICSSCENE_H

#include <qgraphicsscene.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsScene : public QGraphicsScene
{
public:
    QtScriptShell_QGraphicsScene(QObject*  parent = 0);
    QtScriptShell_QGraphicsScene(const QRectF&  sceneRect, QObject*  parent = 0);
    QtScriptShell_QGraphicsScene(qreal  x, qreal  y, qreal  width, qreal  height, QObject*  parent = 0);
    ~QtScriptShell_QGraphicsScene();

    void childEvent(QChildEvent*  arg__1);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*  event);
    void customEvent(QEvent*  arg__1);
    void dragEnterEvent(QGraphicsSceneDragDropEvent*  event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*  event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent*  event);
    void drawBackground(QPainter*  painter, const QRectF&  rect);
    void drawForeground(QPainter*  painter, const QRectF&  rect);
    void drawItems(QPainter*  painter, int  numItems, QGraphicsItem**  items, const QStyleOptionGraphicsItem*  options, QWidget*  widget = 0);
    void dropEvent(QGraphicsSceneDragDropEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void focusInEvent(QFocusEvent*  event);
    void focusOutEvent(QFocusEvent*  event);
    void helpEvent(QGraphicsSceneHelpEvent*  event);
    void inputMethodEvent(QInputMethodEvent*  event);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*  event);
    void mousePressEvent(QGraphicsSceneMouseEvent*  event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);
    void wheelEvent(QGraphicsSceneWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSSCENE_H
