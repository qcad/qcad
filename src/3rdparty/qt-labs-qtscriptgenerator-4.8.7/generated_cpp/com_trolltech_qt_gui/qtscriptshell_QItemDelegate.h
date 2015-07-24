#ifndef QTSCRIPTSHELL_QITEMDELEGATE_H
#define QTSCRIPTSHELL_QITEMDELEGATE_H

#include <qitemdelegate.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QItemDelegate : public QItemDelegate
{
public:
    QtScriptShell_QItemDelegate(QObject*  parent = 0);
    ~QtScriptShell_QItemDelegate();

    void childEvent(QChildEvent*  arg__1);
    QWidget*  createEditor(QWidget*  parent, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void customEvent(QEvent*  arg__1);
    void drawCheck(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect, Qt::CheckState  state) const;
    void drawDecoration(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect, const QPixmap&  pixmap) const;
    void drawDisplay(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect, const QString&  text) const;
    void drawFocus(QPainter*  painter, const QStyleOptionViewItem&  option, const QRect&  rect) const;
    bool  editorEvent(QEvent*  event, QAbstractItemModel*  model, const QStyleOptionViewItem&  option, const QModelIndex&  index);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  object, QEvent*  event);
    void paint(QPainter*  painter, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void setEditorData(QWidget*  editor, const QModelIndex&  index) const;
    void setModelData(QWidget*  editor, QAbstractItemModel*  model, const QModelIndex&  index) const;
    QSize  sizeHint(const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void timerEvent(QTimerEvent*  arg__1);
    void updateEditorGeometry(QWidget*  editor, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QITEMDELEGATE_H
