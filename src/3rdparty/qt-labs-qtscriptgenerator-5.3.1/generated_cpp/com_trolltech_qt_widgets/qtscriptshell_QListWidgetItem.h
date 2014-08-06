#ifndef QTSCRIPTSHELL_QLISTWIDGETITEM_H
#define QTSCRIPTSHELL_QLISTWIDGETITEM_H

#include <qlistwidget.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QListWidgetItem : public QListWidgetItem
{
public:
    QtScriptShell_QListWidgetItem(QListWidget*  view = 0, int  type = Type);
    QtScriptShell_QListWidgetItem(const QIcon&  icon, const QString&  text, QListWidget*  view = 0, int  type = Type);
    QtScriptShell_QListWidgetItem(const QListWidgetItem&  other);
    QtScriptShell_QListWidgetItem(const QString&  text, QListWidget*  view = 0, int  type = Type);
    ~QtScriptShell_QListWidgetItem();

    QListWidgetItem*  clone() const;
    QVariant  data(int  role) const;
    void setData(int  role, const QVariant&  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QLISTWIDGETITEM_H
