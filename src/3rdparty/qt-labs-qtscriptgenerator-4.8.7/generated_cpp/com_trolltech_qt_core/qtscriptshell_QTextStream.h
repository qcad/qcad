#ifndef QTSCRIPTSHELL_QTEXTSTREAM_H
#define QTSCRIPTSHELL_QTEXTSTREAM_H

#include <qtextstream.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextStream : public QTextStream
{
public:
    QtScriptShell_QTextStream();
    QtScriptShell_QTextStream(QByteArray*  array, QIODevice::OpenMode  openMode = QIODevice::ReadWrite);
    QtScriptShell_QTextStream(QIODevice*  device);
    QtScriptShell_QTextStream(QString*  string, QIODevice::OpenMode  openMode = QIODevice::ReadWrite);
    QtScriptShell_QTextStream(const QByteArray&  array, QIODevice::OpenMode  openMode = QIODevice::ReadOnly);
    ~QtScriptShell_QTextStream();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTSTREAM_H
