#include "qtscriptshell_QTextBlockFormat.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qlist.h>
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextBlockFormat::QtScriptShell_QTextBlockFormat()
    : QTextBlockFormat() {}

QtScriptShell_QTextBlockFormat::QtScriptShell_QTextBlockFormat(const QTextFormat&  fmt)
    : QTextBlockFormat(fmt) {}

QtScriptShell_QTextBlockFormat::~QtScriptShell_QTextBlockFormat() {}

