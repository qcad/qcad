#ifndef QTSCRIPTSHELL_QSTANDARDITEM_H
#define QTSCRIPTSHELL_QSTANDARDITEM_H

#include <qstandarditemmodel.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStandardItem : public QStandardItem
{
public:
    QtScriptShell_QStandardItem();
    QtScriptShell_QStandardItem(const QIcon&  icon, const QString&  text);
    QtScriptShell_QStandardItem(const QStandardItem&  other);
    QtScriptShell_QStandardItem(const QString&  text);
    QtScriptShell_QStandardItem(int  rows, int  columns = 1);
    ~QtScriptShell_QStandardItem();

    QStandardItem*  clone() const;
    QVariant  data(int  role = Qt::UserRole + 1) const;
    void setData(const QVariant&  value, int  role = Qt::UserRole + 1);
    int  type() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTANDARDITEM_H
