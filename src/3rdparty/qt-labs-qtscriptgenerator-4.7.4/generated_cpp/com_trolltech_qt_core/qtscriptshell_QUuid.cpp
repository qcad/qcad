#include "qtscriptshell_QUuid.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qdatastream.h>
#include <quuid.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QUuid::QtScriptShell_QUuid()
    : QUuid() {}

QtScriptShell_QUuid::QtScriptShell_QUuid(const QString&  arg__1)
    : QUuid(arg__1) {}

QtScriptShell_QUuid::QtScriptShell_QUuid(uint  l, ushort  w1, ushort  w2, uchar  b1, uchar  b2, uchar  b3, uchar  b4, uchar  b5, uchar  b6, uchar  b7, uchar  b8)
    : QUuid(l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) {}

QtScriptShell_QUuid::~QtScriptShell_QUuid() {}

