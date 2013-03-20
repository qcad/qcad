#ifndef QTSCRIPTSHELL_QABSTRACTPROXYMODEL_H
#define QTSCRIPTSHELL_QABSTRACTPROXYMODEL_H

#include <qabstractproxymodel.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractProxyModel : public QAbstractProxyModel
{
public:
    QtScriptShell_QAbstractProxyModel(QObject*  parent = 0);
    ~QtScriptShell_QAbstractProxyModel();

    QModelIndex  buddy(const QModelIndex&  index) const;
    bool  canFetchMore(const QModelIndex&  parent) const;
    void childEvent(QChildEvent*  arg__1);
    int  columnCount(const QModelIndex&  parent) const;
    void customEvent(QEvent*  arg__1);
    QVariant  data(const QModelIndex&  proxyIndex, int  role = Qt::DisplayRole) const;
    bool  dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fetchMore(const QModelIndex&  parent);
    Qt::ItemFlags  flags(const QModelIndex&  index) const;
    bool  hasChildren(const QModelIndex&  parent) const;
    QVariant  headerData(int  section, Qt::Orientation  orientation, int  role) const;
    QModelIndex  index(int  row, int  column, const QModelIndex&  parent) const;
    bool  insertColumns(int  column, int  count, const QModelIndex&  parent);
    bool  insertRows(int  row, int  count, const QModelIndex&  parent);
    QMap<int , QVariant >  itemData(const QModelIndex&  index) const;
    QModelIndex  mapFromSource(const QModelIndex&  sourceIndex) const;
    QItemSelection  mapSelectionFromSource(const QItemSelection&  selection) const;
    QItemSelection  mapSelectionToSource(const QItemSelection&  selection) const;
    QModelIndex  mapToSource(const QModelIndex&  proxyIndex) const;
    QList<QModelIndex >  match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const;
    QMimeData*  mimeData(const QList<QModelIndex >&  indexes) const;
    QStringList  mimeTypes() const;
    QModelIndex  parent(const QModelIndex&  child) const;
    bool  removeColumns(int  column, int  count, const QModelIndex&  parent);
    bool  removeRows(int  row, int  count, const QModelIndex&  parent);
    void revert();
    int  rowCount(const QModelIndex&  parent) const;
    bool  setData(const QModelIndex&  index, const QVariant&  value, int  role = Qt::EditRole);
    bool  setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role = Qt::EditRole);
    bool  setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles);
    void setSourceModel(QAbstractItemModel*  sourceModel);
    void sort(int  column, Qt::SortOrder  order);
    QSize  span(const QModelIndex&  index) const;
    bool  submit();
    Qt::DropActions  supportedDropActions() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTPROXYMODEL_H
