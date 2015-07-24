#ifndef QTSCRIPTSHELL_QURLINFO_H
#define QTSCRIPTSHELL_QURLINFO_H

#include <qurlinfo.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QUrlInfo : public QUrlInfo
{
public:
    QtScriptShell_QUrlInfo();
    QtScriptShell_QUrlInfo(const QString&  name, int  permissions, const QString&  owner, const QString&  group, qint64  size, const QDateTime&  lastModified, const QDateTime&  lastRead, bool  isDir, bool  isFile, bool  isSymLink, bool  isWritable, bool  isReadable, bool  isExecutable);
    QtScriptShell_QUrlInfo(const QUrl&  url, int  permissions, const QString&  owner, const QString&  group, qint64  size, const QDateTime&  lastModified, const QDateTime&  lastRead, bool  isDir, bool  isFile, bool  isSymLink, bool  isWritable, bool  isReadable, bool  isExecutable);
    QtScriptShell_QUrlInfo(const QUrlInfo&  ui);
    ~QtScriptShell_QUrlInfo();

    void setDir(bool  b);
    void setFile(bool  b);
    void setGroup(const QString&  s);
    void setLastModified(const QDateTime&  dt);
    void setName(const QString&  name);
    void setOwner(const QString&  s);
    void setPermissions(int  p);
    void setReadable(bool  b);
    void setSize(qint64  size);
    void setSymLink(bool  b);
    void setWritable(bool  b);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QURLINFO_H
