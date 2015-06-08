#include "qtscriptshell_QTextImageFormat.h"

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


QtScriptShell_QTextImageFormat::QtScriptShell_QTextImageFormat()
    : QTextImageFormat() {}

QtScriptShell_QTextImageFormat::QtScriptShell_QTextImageFormat(const QTextFormat&  format)
    : QTextImageFormat(format) {}

QtScriptShell_QTextImageFormat::~QtScriptShell_QTextImageFormat() {}

