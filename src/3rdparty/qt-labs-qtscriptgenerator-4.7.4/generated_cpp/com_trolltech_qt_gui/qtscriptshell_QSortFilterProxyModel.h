#ifndef QTSCRIPTSHELL_QSORTFILTERPROXYMODEL_H
#define QTSCRIPTSHELL_QSORTFILTERPROXYMODEL_H

#include <qsortfilterproxymodel.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    QtScriptShell_QSortFilterProxyModel(QObject*  parent = 0);
    ~QtScriptShell_QSortFilterProxyModel();

    bool  filterAcceptsColumn(int  source_column, const QModelIndex&  source_parent) const;
    bool  filterAcceptsRow(int  source_row, const QModelIndex&  source_parent) const;
    bool  lessThan(const QModelIndex&  left, const QModelIndex&  right) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSORTFILTERPROXYMODEL_H
