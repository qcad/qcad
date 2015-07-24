#ifndef QTSCRIPTSHELL_QSQLDRIVERCREATORBASE_H
#define QTSCRIPTSHELL_QSQLDRIVERCREATORBASE_H

#include <qsqldatabase.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSqlDriverCreatorBase : public QSqlDriverCreatorBase
{
public:
    QtScriptShell_QSqlDriverCreatorBase();
    ~QtScriptShell_QSqlDriverCreatorBase();

    QSqlDriver*  createObject() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSQLDRIVERCREATORBASE_H
