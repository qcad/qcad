#include "qtscriptshell_QSqlDatabase.h"

#include <QtScript/QScriptEngine>
#include <QSize>
#include <QSqlError>
#include <QSqlIndex>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QVariant>
#include <qsqldatabase.h>
#include <qsqldriver.h>
#include <qsqlerror.h>
#include <qsqlindex.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QSqlDatabase::QtScriptShell_QSqlDatabase()
    : QSqlDatabase() {}

QtScriptShell_QSqlDatabase::QtScriptShell_QSqlDatabase(QSqlDriver*  driver)
    : QSqlDatabase(driver) {}

QtScriptShell_QSqlDatabase::QtScriptShell_QSqlDatabase(const QSqlDatabase&  other)
    : QSqlDatabase(other) {}

QtScriptShell_QSqlDatabase::QtScriptShell_QSqlDatabase(const QString&  type)
    : QSqlDatabase(type) {}

QtScriptShell_QSqlDatabase::~QtScriptShell_QSqlDatabase() {}

