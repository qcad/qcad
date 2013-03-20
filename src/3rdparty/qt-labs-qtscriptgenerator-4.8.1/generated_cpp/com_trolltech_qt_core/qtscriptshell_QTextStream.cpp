#include "qtscriptshell_QTextStream.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qlocale.h>
#include <qtextcodec.h>
#include <qtextstream.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextStream::QtScriptShell_QTextStream()
    : QTextStream() {}

QtScriptShell_QTextStream::QtScriptShell_QTextStream(QIODevice*  device)
    : QTextStream(device) {}

QtScriptShell_QTextStream::QtScriptShell_QTextStream(const QByteArray&  array, QIODevice::OpenMode  openMode)
    : QTextStream(array, openMode) {}

QtScriptShell_QTextStream::~QtScriptShell_QTextStream() {}

