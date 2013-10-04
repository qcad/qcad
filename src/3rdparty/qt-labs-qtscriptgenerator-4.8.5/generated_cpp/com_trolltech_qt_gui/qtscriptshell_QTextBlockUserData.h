#ifndef QTSCRIPTSHELL_QTEXTBLOCKUSERDATA_H
#define QTSCRIPTSHELL_QTEXTBLOCKUSERDATA_H

#include <qtextobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextBlockUserData : public QTextBlockUserData
{
public:
    QtScriptShell_QTextBlockUserData();
    ~QtScriptShell_QTextBlockUserData();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTBLOCKUSERDATA_H
