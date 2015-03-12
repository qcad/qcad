#ifndef QTSCRIPTSHELL_QUUID_H
#define QTSCRIPTSHELL_QUUID_H

#include <quuid.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QUuid : public QUuid
{
public:
    QtScriptShell_QUuid();
    QtScriptShell_QUuid(const QByteArray&  arg__1);
    QtScriptShell_QUuid(const QString&  arg__1);
    QtScriptShell_QUuid(const char*  arg__1);
    QtScriptShell_QUuid(uint  l, ushort  w1, ushort  w2, uchar  b1, uchar  b2, uchar  b3, uchar  b4, uchar  b5, uchar  b6, uchar  b7, uchar  b8);
    ~QtScriptShell_QUuid();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUUID_H
