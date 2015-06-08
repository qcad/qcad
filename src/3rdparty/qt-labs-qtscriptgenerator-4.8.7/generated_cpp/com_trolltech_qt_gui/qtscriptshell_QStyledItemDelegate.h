#ifndef QTSCRIPTSHELL_QSTYLEDITEMDELEGATE_H
#define QTSCRIPTSHELL_QSTYLEDITEMDELEGATE_H

#include <qstyleditemdelegate.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyledItemDelegate : public QStyledItemDelegate
{
public:
    QtScriptShell_QStyledItemDelegate(QObject*  parent = 0);
    ~QtScriptShell_QStyledItemDelegate();

    void childEvent(QChildEvent*  arg__1);
    QWidget*  createEditor(QWidget*  parent, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void customEvent(QEvent*  arg__1);
    QString  displayText(const QVariant&  value, const QLocale&  locale) const;
    bool  editorEvent(QEvent*  event, QAbstractItemModel*  model, const QStyleOptionViewItem&  option, const QModelIndex&  index);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  object, QEvent*  event);
    void initStyleOption(QStyleOptionViewItem*  option, const QModelIndex&  index) const;
    void paint(QPainter*  painter, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void setEditorData(QWidget*  editor, const QModelIndex&  index) const;
    void setModelData(QWidget*  editor, QAbstractItemModel*  model, const QModelIndex&  index) const;
    QSize  sizeHint(const QStyleOptionViewItem&  option, const QModelIndex&  index) const;
    void timerEvent(QTimerEvent*  arg__1);
    void updateEditorGeometry(QWidget*  editor, const QStyleOptionViewItem&  option, const QModelIndex&  index) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEDITEMDELEGATE_H
