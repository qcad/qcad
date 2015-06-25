#ifndef QTSCRIPTSHELL_QGRAPHICSWEBVIEW_H
#define QTSCRIPTSHELL_QGRAPHICSWEBVIEW_H

#include <qgraphicswebview.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsWebView : public QGraphicsWebView
{
public:
    QtScriptShell_QGraphicsWebView(QGraphicsItem*  parent = 0);
    ~QtScriptShell_QGraphicsWebView();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent*  arg__1);
    void dragEnterEvent(QGraphicsSceneDragDropEvent*  arg__1);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*  arg__1);
    void dragMoveEvent(QGraphicsSceneDragDropEvent*  arg__1);
    void dropEvent(QGraphicsSceneDragDropEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    void focusInEvent(QFocusEvent*  arg__1);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  arg__1);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*  arg__1);
    void hoverMoveEvent(QGraphicsSceneHoverEvent*  arg__1);
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    void keyPressEvent(QKeyEvent*  arg__1);
    void keyReleaseEvent(QKeyEvent*  arg__1);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  arg__1);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*  arg__1);
    void mousePressEvent(QGraphicsSceneMouseEvent*  arg__1);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*  arg__1);
    void paint(QPainter*  arg__1, const QStyleOptionGraphicsItem*  options, QWidget*  widget = 0);
    bool  sceneEvent(QEvent*  arg__1);
    void setGeometry(const QRectF&  rect);
    QSizeF  sizeHint(Qt::SizeHint  which, const QSizeF&  constraint) const;
    void updateGeometry();
    void wheelEvent(QGraphicsSceneWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSWEBVIEW_H
