#ifndef QTSCRIPTSHELL_QSQLDATABASE_H
#define QTSCRIPTSHELL_QSQLDATABASE_H

#include <qsqldatabase.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSqlDatabase : public QSqlDatabase
{
public:
    QtScriptShell_QSqlDatabase();
    QtScriptShell_QSqlDatabase(QSqlDriver*  driver);
    QtScriptShell_QSqlDatabase(const QSqlDatabase&  other);
    QtScriptShell_QSqlDatabase(const QString&  type);
    ~QtScriptShell_QSqlDatabase();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSQLDATABASE_H
