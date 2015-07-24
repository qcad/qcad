#ifndef QTSCRIPTSHELL_QSQLDRIVER_H
#define QTSCRIPTSHELL_QSQLDRIVER_H

#include <qsqldriver.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSqlDriver : public QSqlDriver
{
public:
    QtScriptShell_QSqlDriver(QObject*  parent = 0);
    ~QtScriptShell_QSqlDriver();

    bool  beginTransaction();
    bool  cancelQuery();
    void childEvent(QChildEvent*  arg__1);
    void close();
    bool  commitTransaction();
    QSqlResult*  createResult() const;
    void customEvent(QEvent*  arg__1);
    QString  escapeIdentifier(const QString&  identifier, QSqlDriver::IdentifierType  type) const;
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QString  formatValue(const QSqlField&  field, bool  trimStrings = false) const;
    QVariant  handle() const;
    bool  hasFeature(QSqlDriver::DriverFeature  f) const;
    bool  isIdentifierEscaped(const QString&  identifier, QSqlDriver::IdentifierType  type) const;
    bool  isOpen() const;
    bool  open(const QString&  db, const QString&  user = QString(), const QString&  password = QString(), const QString&  host = QString(), int  port = -1, const QString&  connOpts = QString());
    QSqlIndex  primaryIndex(const QString&  tableName) const;
    QSqlRecord  record(const QString&  tableName) const;
    bool  rollbackTransaction();
    void setLastError(const QSqlError&  e);
    void setOpen(bool  o);
    void setOpenError(bool  e);
    QString  sqlStatement(QSqlDriver::StatementType  type, const QString&  tableName, const QSqlRecord&  rec, bool  preparedStatement) const;
    QString  stripDelimiters(const QString&  identifier, QSqlDriver::IdentifierType  type) const;
    bool  subscribeToNotification(const QString&  name);
    QStringList  subscribedToNotifications() const;
    QStringList  tables(QSql::TableType  tableType) const;
    void timerEvent(QTimerEvent*  arg__1);
    bool  unsubscribeFromNotification(const QString&  name);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSQLDRIVER_H
