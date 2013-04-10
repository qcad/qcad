#ifndef QTSCRIPTSHELL_QABSTRACTNETWORKCACHE_H
#define QTSCRIPTSHELL_QABSTRACTNETWORKCACHE_H

#include <qabstractnetworkcache.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractNetworkCache : public QAbstractNetworkCache
{
public:
    QtScriptShell_QAbstractNetworkCache(QObject*  parent = 0);
    ~QtScriptShell_QAbstractNetworkCache();

    qint64  cacheSize() const;
    void childEvent(QChildEvent*  arg__1);
    void clear();
    void customEvent(QEvent*  arg__1);
    QIODevice*  data(const QUrl&  url);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void insert(QIODevice*  device);
    QNetworkCacheMetaData  metaData(const QUrl&  url);
    QIODevice*  prepare(const QNetworkCacheMetaData&  metaData);
    bool  remove(const QUrl&  url);
    void timerEvent(QTimerEvent*  arg__1);
    void updateMetaData(const QNetworkCacheMetaData&  metaData);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTNETWORKCACHE_H
