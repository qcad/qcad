#include "qtscriptshell_QPixmapCache.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qpixmap.h>
#include <qpixmapcache.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QPixmapCache::QtScriptShell_QPixmapCache()
    : QPixmapCache() {}

QtScriptShell_QPixmapCache::~QtScriptShell_QPixmapCache() {}

