#ifndef QTSCRIPTSHELL_QABSTRACTITEMDELEGATE_H
#define QTSCRIPTSHELL_QABSTRACTITEMDELEGATE_H

#include <qabstractitemdelegate.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractItemDelegate : public QAbstractItemDelegate
{
public:
    QtScriptShell_QAbstractItemDelegate(QObject*  parent = 0);
    ~QtScriptShell_QAbstractItemDelegate();

    void childEvent(QChildEvent*  arg__1);
    QWidget*  createEditor(QWidget*  parent, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void customEvent(QEvent*  arg__1);
    bool  editorEvent(QEvent*  event, QAbstractItemModel*  model, const QStyleOptionViewItem&  option, const QModelIndex&  index);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void paint(QPainter*  painter, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void setEditorData(QWidget*  editor, const QModelIndex&  index) const;
    void setModelData(QWidget*  editor, QAbstractItemModel*  model, const QModelIndex&  index) const;
    QSize  sizeHint(const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void timerEvent(QTimerEvent*  arg__1);
    void updateEditorGeometry(QWidget*  editor, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTITEMDELEGATE_H
