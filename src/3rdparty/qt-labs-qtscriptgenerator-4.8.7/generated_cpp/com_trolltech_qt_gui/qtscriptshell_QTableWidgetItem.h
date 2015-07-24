#ifndef QTSCRIPTSHELL_QTABLEWIDGETITEM_H
#define QTSCRIPTSHELL_QTABLEWIDGETITEM_H

#include <qtablewidget.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTableWidgetItem : public QTableWidgetItem
{
public:
    QtScriptShell_QTableWidgetItem(const QIcon&  icon, const QString&  text, int  type = Type);
    QtScriptShell_QTableWidgetItem(const QString&  text, int  type = Type);
    QtScriptShell_QTableWidgetItem(const QTableWidgetItem&  other);
    QtScriptShell_QTableWidgetItem(int  type = Type);
    ~QtScriptShell_QTableWidgetItem();

    QTableWidgetItem*  clone() const;
    QVariant  data(int  role) const;
    void setData(int  role, const QVariant&  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTABLEWIDGETITEM_H
