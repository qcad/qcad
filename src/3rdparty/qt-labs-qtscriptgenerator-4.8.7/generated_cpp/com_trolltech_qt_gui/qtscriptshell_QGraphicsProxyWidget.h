#ifndef QTSCRIPTSHELL_QGRAPHICSPROXYWIDGET_H
#define QTSCRIPTSHELL_QGRAPHICSPROXYWIDGET_H

#include <qgraphicsproxywidget.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    QtScriptShell_QGraphicsProxyWidget(QGraphicsItem*  parent = 0, Qt::WindowFlags  wFlags = 0);
    ~QtScriptShell_QGraphicsProxyWidget();

    void advance(int  phase);
    QRectF  boundingRect() const;
    void changeEvent(QEvent*  event);
    void childEvent(QChildEvent*  arg__1);
    void closeEvent(QCloseEvent*  event);
    bool  collidesWithItem(const QGraphicsItem*  other, Qt::ItemSelectionMode  mode) const;
    bool  collidesWithPath(const QPainterPath&  path, Qt::ItemSelectionMode  mode) const;
    bool  contains(const QPointF&  point) const;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent*  event);
    void customEvent(QEvent*  arg__1);
    void dragEnterEvent(QGraphicsSceneDragDropEvent*  event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*  event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent*  event);
    void dropEvent(QGraphicsSceneDragDropEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  object, QEvent*  event);
    QVariant  extension(const QVariant&  variant) const;
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    void getContentsMargins(qreal*  left, qreal*  top, qreal*  right, qreal*  bottom) const;
    void grabKeyboardEvent(QEvent*  event);
    void grabMouseEvent(QEvent*  event);
    void hideEvent(QHideEvent*  event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*  event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*  event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent*  event);
    void initStyleOption(QStyleOption*  option) const;
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
    void moveEvent(QGraphicsSceneMoveEvent*  event);
    QPainterPath  opaqueArea() const;
    void paint(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget);
    void paintWindowFrame(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget);
    void polishEvent();
    QVariant  propertyChange(const QString&  propertyName, const QVariant&  value);
    void resizeEvent(QGraphicsSceneResizeEvent*  event);
    bool  sceneEvent(QEvent*  event);
    bool  sceneEventFilter(QGraphicsItem*  watched, QEvent*  event);
    void setGeometry(const QRectF&  rect);
    QPainterPath  shape() const;
    void showEvent(QShowEvent*  event);
    QSizeF  sizeHint(Qt::SizeHint  which, const QSizeF&  constraint = QSizeF()) const;
    void timerEvent(QTimerEvent*  arg__1);
    int  type() const;
    void ungrabKeyboardEvent(QEvent*  event);
    void ungrabMouseEvent(QEvent*  event);
    void updateGeometry();
    void wheelEvent(QGraphicsSceneWheelEvent*  event);
    bool  windowFrameEvent(QEvent*  e);
    Qt::WindowFrameSection  windowFrameSectionAt(const QPointF&  pos) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSPROXYWIDGET_H
