#ifndef QTSCRIPTSHELL_QTREEWIDGETITEM_H
#define QTSCRIPTSHELL_QTREEWIDGETITEM_H

#include <qtreewidget.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTreeWidgetItem : public QTreeWidgetItem
{
public:
    QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, QTreeWidgetItem*  after, int  type = Type);
    QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, const QStringList&  strings, int  type = Type);
    QtScriptShell_QTreeWidgetItem(QTreeWidget*  view, int  type = Type);
    QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, QTreeWidgetItem*  after, int  type = Type);
    QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, const QStringList&  strings, int  type = Type);
    QtScriptShell_QTreeWidgetItem(QTreeWidgetItem*  parent, int  type = Type);
    QtScriptShell_QTreeWidgetItem(const QStringList&  strings, int  type = Type);
    QtScriptShell_QTreeWidgetItem(const QTreeWidgetItem&  other);
    QtScriptShell_QTreeWidgetItem(int  type = Type);
    ~QtScriptShell_QTreeWidgetItem();

    QTreeWidgetItem*  clone() const;
    QVariant  data(int  column, int  role) const;
    void setData(int  column, int  role, const QVariant&  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTREEWIDGETITEM_H
