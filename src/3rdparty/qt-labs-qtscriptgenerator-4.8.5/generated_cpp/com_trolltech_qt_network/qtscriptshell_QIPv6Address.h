#ifndef QTSCRIPTSHELL_QIPV6ADDRESS_H
#define QTSCRIPTSHELL_QIPV6ADDRESS_H

#include <qhostaddress.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QIPv6Address : public QIPv6Address
{
public:
    QtScriptShell_QIPv6Address();
    ~QtScriptShell_QIPv6Address();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QIPV6ADDRESS_H
