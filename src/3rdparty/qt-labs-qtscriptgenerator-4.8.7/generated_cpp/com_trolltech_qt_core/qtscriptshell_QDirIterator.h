#ifndef QTSCRIPTSHELL_QDIRITERATOR_H
#define QTSCRIPTSHELL_QDIRITERATOR_H

#include <qdiriterator.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QDirIterator : public QDirIterator
{
public:
    QtScriptShell_QDirIterator(const QDir&  dir, QDirIterator::IteratorFlags  flags = NoIteratorFlags);
    QtScriptShell_QDirIterator(const QString&  path, QDir::Filters  filter, QDirIterator::IteratorFlags  flags = NoIteratorFlags);
    QtScriptShell_QDirIterator(const QString&  path, QDirIterator::IteratorFlags  flags = NoIteratorFlags);
    QtScriptShell_QDirIterator(const QString&  path, const QStringList&  nameFilters, QDir::Filters  filters = QDir::NoFilter, QDirIterator::IteratorFlags  flags = NoIteratorFlags);
    ~QtScriptShell_QDirIterator();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDIRITERATOR_H
