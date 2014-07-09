#ifndef QTSCRIPTSHELL_QSQLRESULT_H
#define QTSCRIPTSHELL_QSQLRESULT_H

#include <qsqlresult.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSqlResult : public QSqlResult
{
public:
    QtScriptShell_QSqlResult(const QSqlDriver*  db);
    ~QtScriptShell_QSqlResult();

    void bindValue(const QString&  placeholder, const QVariant&  val, QSql::ParamType  type);
    void bindValue(int  pos, const QVariant&  val, QSql::ParamType  type);
    QVariant  data(int  i);
    bool  exec();
    bool  fetch(int  i);
    bool  fetchFirst();
    bool  fetchLast();
    bool  fetchNext();
    bool  fetchPrevious();
    QVariant  handle() const;
    bool  isNull(int  i);
    QVariant  lastInsertId() const;
    int  numRowsAffected();
    bool  prepare(const QString&  query);
    QSqlRecord  record() const;
    bool  reset(const QString&  sqlquery);
    bool  savePrepare(const QString&  sqlquery);
    void setActive(bool  a);
    void setAt(int  at);
    void setForwardOnly(bool  forward);
    void setLastError(const QSqlError&  e);
    void setQuery(const QString&  query);
    void setSelect(bool  s);
    int  size();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSQLRESULT_H
