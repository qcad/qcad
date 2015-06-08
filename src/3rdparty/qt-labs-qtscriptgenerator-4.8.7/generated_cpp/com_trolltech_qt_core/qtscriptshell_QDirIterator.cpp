#include "qtscriptshell_QDirIterator.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qdir.h>
#include <qdiriterator.h>
#include <qfileinfo.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QDirIterator::QtScriptShell_QDirIterator(const QDir&  dir, QDirIterator::IteratorFlags  flags)
    : QDirIterator(dir, flags) {}

QtScriptShell_QDirIterator::QtScriptShell_QDirIterator(const QString&  path, QDir::Filters  filter, QDirIterator::IteratorFlags  flags)
    : QDirIterator(path, filter, flags) {}

QtScriptShell_QDirIterator::QtScriptShell_QDirIterator(const QString&  path, QDirIterator::IteratorFlags  flags)
    : QDirIterator(path, flags) {}

QtScriptShell_QDirIterator::QtScriptShell_QDirIterator(const QString&  path, const QStringList&  nameFilters, QDir::Filters  filters, QDirIterator::IteratorFlags  flags)
    : QDirIterator(path, nameFilters, filters, flags) {}

QtScriptShell_QDirIterator::~QtScriptShell_QDirIterator() {}

