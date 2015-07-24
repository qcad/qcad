#include "qtscriptshell_QTextCharFormat.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qfont.h>
#include <qpen.h>
#include <qstringlist.h>
#include <qtextformat.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextCharFormat::QtScriptShell_QTextCharFormat()
    : QTextCharFormat() {}

QtScriptShell_QTextCharFormat::QtScriptShell_QTextCharFormat(const QTextFormat&  fmt)
    : QTextCharFormat(fmt) {}

QtScriptShell_QTextCharFormat::~QtScriptShell_QTextCharFormat() {}

