#include "qtscriptshell_QTextTableFormat.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qpen.h>
#include <qtextformat.h>
#include <qvector.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextTableFormat::QtScriptShell_QTextTableFormat()
    : QTextTableFormat() {}

QtScriptShell_QTextTableFormat::QtScriptShell_QTextTableFormat(const QTextFormat&  fmt)
    : QTextTableFormat(fmt) {}

QtScriptShell_QTextTableFormat::~QtScriptShell_QTextTableFormat() {}

