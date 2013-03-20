#include "qtscriptshell_QTextListFormat.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextListFormat::QtScriptShell_QTextListFormat()
    : QTextListFormat() {}

QtScriptShell_QTextListFormat::QtScriptShell_QTextListFormat(const QTextFormat&  fmt)
    : QTextListFormat(fmt) {}

QtScriptShell_QTextListFormat::~QtScriptShell_QTextListFormat() {}

