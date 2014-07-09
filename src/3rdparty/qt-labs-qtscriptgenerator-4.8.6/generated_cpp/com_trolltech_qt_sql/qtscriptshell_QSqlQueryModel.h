#ifndef QTSCRIPTSHELL_QSQLQUERYMODEL_H
#define QTSCRIPTSHELL_QSQLQUERYMODEL_H

#include <qsqlquerymodel.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSqlQueryModel : public QSqlQueryModel
{
public:
    QtScriptShell_QSqlQueryModel(QObject*  parent = 0);
    ~QtScriptShell_QSqlQueryModel();

    QModelIndex  buddy(const QModelIndex&  index) const;
    bool  canFetchMore(const QModelIndex&  parent = QModelIndex()) const;
    void childEvent(QChildEvent*  arg__1);
    void clear();
    int  columnCount(const QModelIndex&  parent = QModelIndex()) const;
    void customEvent(QEvent*  arg__1);
    QVariant  data(const QModelIndex&  item, int  role = Qt::DisplayRole) const;
    bool  dropMimeData(const QMimeData*  data, Qt::DropAction  action, int  row, int  column, const QModelIndex&  parent);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fetchMore(const QModelIndex&  parent = QModelIndex());
    Qt::ItemFlags  flags(const QModelIndex&  index) const;
    QVariant  headerData(int  section, Qt::Orientation  orientation, int  role = Qt::DisplayRole) const;
    QModelIndex  index(int  row, int  column, const QModelIndex&  parent) const;
    bool  insertColumns(int  column, int  count, const QModelIndex&  parent = QModelIndex());
    bool  insertRows(int  row, int  count, const QModelIndex&  parent);
    QMap<int , QVariant >  itemData(const QModelIndex&  index) const;
    QList<QModelIndex >  match(const QModelIndex&  start, int  role, const QVariant&  value, int  hits, Qt::MatchFlags  flags) const;
    QMimeData*  mimeData(const QList<QModelIndex >&  indexes) const;
    QStringList  mimeTypes() const;
    void queryChange();
    bool  removeColumns(int  column, int  count, const QModelIndex&  parent = QModelIndex());
    bool  removeRows(int  row, int  count, const QModelIndex&  parent);
    void revert();
    int  rowCount(const QModelIndex&  parent = QModelIndex()) const;
    bool  setData(const QModelIndex&  index, const QVariant&  value, int  role);
    bool  setHeaderData(int  section, Qt::Orientation  orientation, const QVariant&  value, int  role = Qt::EditRole);
    bool  setItemData(const QModelIndex&  index, const QMap<int , QVariant >&  roles);
    void sort(int  column, Qt::SortOrder  order);
    QSize  span(const QModelIndex&  index) const;
    bool  submit();
    Qt::DropActions  supportedDropActions() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSQLQUERYMODEL_H
