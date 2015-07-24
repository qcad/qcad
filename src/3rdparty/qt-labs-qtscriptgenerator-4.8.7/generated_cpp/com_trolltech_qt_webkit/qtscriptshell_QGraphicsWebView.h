#ifndef QTSCRIPTSHELL_QGRAPHICSWEBVIEW_H
#define QTSCRIPTSHELL_QGRAPHICSWEBVIEW_H

#include <qgraphicswebview.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsWebView : public QGraphicsWebView
{
public:
    QtScriptShell_QGraphicsWebView(QGraphicsItem*  parent = 0);
    ~QtScriptShell_QGraphicsWebView();

    void advance(int  phase);
    QRectF  boundingRect() const;
    void changeEvent(QEvent*  event);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  event);
    bool  collidesWithItem(const QGraphicsItem*  other, Qt::ItemSelectionMode  mode) const;
    bool  collidesWithPath(const QPainterPath&  path, Qt::ItemSelectionMode  mode) const;
    bool  contains(const QPointF&  point) const;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void dragEnterEvent(QGraphicsSceneDragDropEvent*  arg__1);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*  arg__1);
    void dragMoveEvent(QGraphicsSceneDragDropEvent*  arg__1);
    void dropEvent(QGraphicsSceneDragDropEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QVariant  extension(const QVariant&  variant) const;
    void focusInEvent(QFocusEvent*  arg__1);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  arg__1);
    void getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const;
    void grabKeyboardEvent(QEvent*  event);
    void grabMouseEvent(QEvent*  event);
    void hideEvent(QHideEvent*  event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*  event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*  arg__1);
    void hoverMoveEvent(QGraphicsSceneHoverEvent*  arg__1);
    void initStyleOption(QStyleOption*  option) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    bool  isObscuredBy(const QGraphicsItem*  item) const;
    QVariant  itemChange(QGraphicsItem::GraphicsItemChange  change, const QVariant&  value);
    void keyPressEvent(QKeyEvent*  arg__1);
    void keyReleaseEvent(QKeyEvent*  arg__1);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*  arg__1);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*  arg__1);
    void mousePressEvent(QGraphicsSceneMouseEvent*  arg__1);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*  arg__1);
    void moveEvent(QGraphicsSceneMoveEvent*  event);
    QPainterPath  opaqueArea() const;
    void paint(QPainter*  arg__1, const QStyleOptionGraphicsItem*  options, QWidget*  widget = 0);
    void paintWindowFrame(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget);
    void polishEvent();
    QVariant  propertyChange(const QString&  propertyName, const QVariant&  value);
    void resizeEvent(QGraphicsSceneResizeEvent*  event);
    bool  sceneEvent(QEvent*  arg__1);
    bool  sceneEventFilter(QGraphicsItem*  watched, QEvent*  event);
    void setGeometry(const QRectF&  rect);
    QPainterPath  shape() const;
    void showEvent(QShowEvent*  event);
    QSizeF  sizeHint(Qt::SizeHint  which, const QSizeF&  constraint) const;
    void timerEvent(QTimerEvent*  arg__1);
    int  type() const;
    void ungrabKeyboardEvent(QEvent*  event);
    void ungrabMouseEvent(QEvent*  event);
    void updateGeometry();
    void wheelEvent(QGraphicsSceneWheelEvent*  arg__1);
    bool  windowFrameEvent(QEvent*  e);
    Qt::WindowFrameSection  windowFrameSectionAt(const QPointF&  pos) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSWEBVIEW_H
