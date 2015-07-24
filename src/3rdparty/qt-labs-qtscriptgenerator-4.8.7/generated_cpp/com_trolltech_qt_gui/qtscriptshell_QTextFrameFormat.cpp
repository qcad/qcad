#include "qtscriptshell_QTextFrameFormat.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextFrameFormat::QtScriptShell_QTextFrameFormat()
    : QTextFrameFormat() {}

QtScriptShell_QTextFrameFormat::QtScriptShell_QTextFrameFormat(const QTextFormat&  fmt)
    : QTextFrameFormat(fmt) {}

QtScriptShell_QTextFrameFormat::~QtScriptShell_QTextFrameFormat() {}

