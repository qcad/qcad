#ifndef QTSCRIPTSHELL_QPIXMAPCACHE_H
#define QTSCRIPTSHELL_QPIXMAPCACHE_H

#include <qpixmapcache.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPixmapCache : public QPixmapCache
{
public:
    QtScriptShell_QPixmapCache();
    ~QtScriptShell_QPixmapCache();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPIXMAPCACHE_H
