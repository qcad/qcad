#include "qtscriptshell_QDataStream.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qiodevice.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QDataStream::QtScriptShell_QDataStream()
    : QDataStream() {}

QtScriptShell_QDataStream::QtScriptShell_QDataStream(QByteArray*  arg__1, QIODevice::OpenMode  flags)
    : QDataStream(arg__1, flags) {}

QtScriptShell_QDataStream::QtScriptShell_QDataStream(QIODevice*  arg__1)
    : QDataStream(arg__1) {}

QtScriptShell_QDataStream::QtScriptShell_QDataStream(const QByteArray&  arg__1)
    : QDataStream(arg__1) {}

QtScriptShell_QDataStream::~QtScriptShell_QDataStream() {}

