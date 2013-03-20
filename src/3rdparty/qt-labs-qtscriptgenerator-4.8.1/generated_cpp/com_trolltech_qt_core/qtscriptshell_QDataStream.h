#ifndef QTSCRIPTSHELL_QDATASTREAM_H
#define QTSCRIPTSHELL_QDATASTREAM_H

#include <qdatastream.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QDataStream : public QDataStream
{
public:
    QtScriptShell_QDataStream();
    QtScriptShell_QDataStream(QByteArray*  arg__1, QIODevice::OpenMode  flags);
    QtScriptShell_QDataStream(QIODevice*  arg__1);
    QtScriptShell_QDataStream(const QByteArray&  arg__1);
    ~QtScriptShell_QDataStream();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDATASTREAM_H
