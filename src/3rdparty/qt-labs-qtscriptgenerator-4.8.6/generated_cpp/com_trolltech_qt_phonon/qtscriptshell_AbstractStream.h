#ifndef QTSCRIPTSHELL_ABSTRACTSTREAM_H
#define QTSCRIPTSHELL_ABSTRACTSTREAM_H

#include <streaminterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractStream : public Phonon::StreamInterface
{
public:
    QtScriptShell_AbstractStream();
    ~QtScriptShell_AbstractStream();

    void endOfData();
    void setStreamSeekable(bool  s);
    void setStreamSize(qint64  newSize);
    void writeData(const QByteArray&  data);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTSTREAM_H
