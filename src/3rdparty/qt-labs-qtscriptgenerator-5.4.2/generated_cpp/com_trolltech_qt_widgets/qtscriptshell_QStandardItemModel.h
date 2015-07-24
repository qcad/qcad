#ifndef QTSCRIPTSHELL_QSTANDARDITEMMODEL_H
#define QTSCRIPTSHELL_QSTANDARDITEMMODEL_H

#include <qstandarditemmodel.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStandardItemModel : public QStandardItemModel
{
public:
    QtScriptShell_QStandardItemModel(QObject*  parent = 0);
    QtScriptShell_QStandardItemModel(int  rows, int  columns, QObject*  parent = 0);
    ~QtScriptShell_QStandardItemModel();

    QModelIndex  buddy(const QModelIndex&  index) const;
    bool  canDropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent) const;
    bool  canFetchMore(const QModelIndex&  parent) const;
    void childEvent(QChildEvent*  arg__1);
    int  columnCount(const QModelIndex&  parent = QModelIndex()) const;
    void customEvent(QEvent*  arg__1);
    QVariant  data(const QModelIndex&  index, int  role = Qt::DisplayRole) const;
    bool  dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fetchMore(const QModelIndex&  parent);
    Qt::ItemFlags  flags(const QModelIndex&  index) const;
    bool  hasChildren(const QModelIndex&  parent = QModelIndex()) const;
    QVariant  headerData(int  section, Qt::Orientation  orientation, int  role = Qt::DisplayRole) const;
    QModelIndex  index(int  row, int  column, const QModelIndex&  parent = QModelIndex()) const;
    bool  insertColumns(int  column, int  count, const QModelIndex&  parent = QModelIndex());
    bool  insertRows(int  row, int  count, const QModelIndex&  parent = QModelIndex());
    QMap<int , QVariant >  itemData(const QModelIndex&  index) const;
    QList<QModelIndex >  match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const;
    QMimeData*  mimeData(const QList<QModelIndex >&  indexes) const;
    QStringList  mimeTypes() const;
    bool  moveColumns(const QModelIndex&  sourceParent, int  sourceColumn, int  count, const QModelIndex&  destinationParent, int  destinationChild);
    bool  moveRows(const QModelIndex&  sourceParent, int  sourceRow, int  count, const QModelIndex&  destinationParent, int  destinationChild);
    QModelIndex  parent(const QModelIndex&  child) const;
    bool  removeColumns(int  column, int  count, const QModelIndex&  parent = QModelIndex());
    bool  removeRows(int  row, int  count, const QModelIndex&  parent = QModelIndex());
    void revert();
    QHash<int , QByteArray >  roleNames() const;
    int  rowCount(const QModelIndex&  parent = QModelIndex()) const;
    bool  setData(const QModelIndex&  index, const QVariant&  value, int  role = Qt::EditRole);
    bool  setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role = Qt::EditRole);
    bool  setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles);
    QModelIndex  sibling(int  row, int  column, const QModelIndex&  idx) const;
    void sort(int  column, Qt::SortOrder  order = Qt::AscendingOrder);
    QSize  span(const QModelIndex&  index) const;
    bool  submit();
    Qt::DropActions  supportedDragActions() const;
    Qt::DropActions  supportedDropActions() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTANDARDITEMMODEL_H
