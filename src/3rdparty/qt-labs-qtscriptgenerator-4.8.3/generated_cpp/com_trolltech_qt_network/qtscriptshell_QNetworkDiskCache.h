#ifndef QTSCRIPTSHELL_QNETWORKDISKCACHE_H
#define QTSCRIPTSHELL_QNETWORKDISKCACHE_H

#include <qnetworkdiskcache.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QNetworkDiskCache : public QNetworkDiskCache
{
public:
    QtScriptShell_QNetworkDiskCache(QObject*  parent = 0);
    ~QtScriptShell_QNetworkDiskCache();

    qint64  cacheSize() const;
    void childEvent(QChildEvent*  arg__1);
    void clear();
    void customEvent(QEvent*  arg__1);
    QIODevice*  data(const QUrl&  url);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    qint64  expire();
    void insert(QIODevice*  device);
    QNetworkCacheMetaData  metaData(const QUrl&  url);
    QIODevice*  prepare(const QNetworkCacheMetaData&  metaData);
    bool  remove(const QUrl&  url);
    void timerEvent(QTimerEvent*  arg__1);
    void updateMetaData(const QNetworkCacheMetaData&  metaData);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKDISKCACHE_H
