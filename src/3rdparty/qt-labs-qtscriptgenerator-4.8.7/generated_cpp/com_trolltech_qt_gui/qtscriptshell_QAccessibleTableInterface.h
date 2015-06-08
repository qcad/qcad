#ifndef QTSCRIPTSHELL_QACCESSIBLETABLEINTERFACE_H
#define QTSCRIPTSHELL_QACCESSIBLETABLEINTERFACE_H

#include <qaccessible2.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleTableInterface : public QAccessibleTableInterface
{
public:
    QtScriptShell_QAccessibleTableInterface();
    ~QtScriptShell_QAccessibleTableInterface();

    QAccessibleInterface*  accessibleAt(int  row, int  column);
    QAccessibleInterface*  caption();
    void cellAtIndex(int  index, int*  row, int*  column, int*  rowSpan, int*  columnSpan, bool*  isSelected);
    int  childIndex(int  rowIndex, int  columnIndex);
    int  columnCount();
    QString  columnDescription(int  column);
    QAccessibleInterface*  columnHeader();
    int  columnIndex(int  childIndex);
    int  columnSpan(int  row, int  column);
    bool  isColumnSelected(int  column);
    bool  isRowSelected(int  row);
    bool  isSelected(int  row, int  column);
    int  rowCount();
    QString  rowDescription(int  row);
    QAccessibleInterface*  rowHeader();
    int  rowIndex(int  childIndex);
    int  rowSpan(int  row, int  column);
    void selectColumn(int  column);
    void selectRow(int  row);
    int  selectedColumnCount();
    int  selectedColumns(int  maxColumns, QList<int >*  columns);
    int  selectedRowCount();
    int  selectedRows(int  maxRows, QList<int >*  rows);
    QAccessibleInterface*  summary();
    void unselectColumn(int  column);
    void unselectRow(int  row);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLETABLEINTERFACE_H
